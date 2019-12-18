#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  ln_nlen; int /*<<< orphan*/  ln_name; int /*<<< orphan*/  nlen; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ARCHD ;

/* Variables and functions */
 scalar_t__ PAX_HLK ; 
 scalar_t__ PAX_HRG ; 
 scalar_t__ fix_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

int
set_dest(ARCHD *arcn, char *dest_dir, int dir_len)
{
	if (fix_path(arcn->name, &(arcn->nlen), dest_dir, dir_len) < 0)
		return(-1);

	/*
	 * It is really hard to deal with symlinks here, we cannot be sure
	 * if the name they point was moved (or will be moved). It is best to
	 * leave them alone.
	 */
	if ((arcn->type != PAX_HLK) && (arcn->type != PAX_HRG))
		return(0);

	if (fix_path(arcn->ln_name, &(arcn->ln_nlen), dest_dir, dir_len) < 0)
		return(-1);
	return(0);
}