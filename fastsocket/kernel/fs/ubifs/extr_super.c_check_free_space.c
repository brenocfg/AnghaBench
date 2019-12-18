#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ total_free; scalar_t__ total_dirty; } ;
struct ubifs_info {scalar_t__ dark_wm; TYPE_1__ lst; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  dbg_dump_budg (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_dump_lprops (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_err (char*) ; 

__attribute__((used)) static int check_free_space(struct ubifs_info *c)
{
	ubifs_assert(c->dark_wm > 0);
	if (c->lst.total_free + c->lst.total_dirty < c->dark_wm) {
		ubifs_err("insufficient free space to mount in read/write mode");
		dbg_dump_budg(c);
		dbg_dump_lprops(c);
		return -ENOSPC;
	}
	return 0;
}