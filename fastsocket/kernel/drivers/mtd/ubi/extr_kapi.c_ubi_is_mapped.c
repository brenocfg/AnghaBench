#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ubi_volume_desc {struct ubi_volume* vol; } ;
struct ubi_volume {int reserved_pebs; scalar_t__* eba_tbl; scalar_t__ upd_marker; int /*<<< orphan*/  vol_id; } ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int) ; 

int ubi_is_mapped(struct ubi_volume_desc *desc, int lnum)
{
	struct ubi_volume *vol = desc->vol;

	dbg_gen("test LEB %d:%d", vol->vol_id, lnum);

	if (lnum < 0 || lnum >= vol->reserved_pebs)
		return -EINVAL;

	if (vol->upd_marker)
		return -EBADF;

	return vol->eba_tbl[lnum] >= 0;
}