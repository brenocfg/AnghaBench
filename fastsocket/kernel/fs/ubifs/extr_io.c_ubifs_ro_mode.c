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
struct ubifs_info {int ro_media; scalar_t__ no_chk_data_crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_dump_stack () ; 
 int /*<<< orphan*/  ubifs_warn (char*,int) ; 

void ubifs_ro_mode(struct ubifs_info *c, int err)
{
	if (!c->ro_media) {
		c->ro_media = 1;
		c->no_chk_data_crc = 0;
		ubifs_warn("switched to read-only mode, error %d", err);
		dbg_dump_stack();
	}
}