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
struct ubifs_scan_leb {int /*<<< orphan*/  endpt; } ;
struct ubifs_info {int min_io_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int /*<<< orphan*/  dbg_scan (char*,int,int) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 

void ubifs_end_scan(const struct ubifs_info *c, struct ubifs_scan_leb *sleb,
		    int lnum, int offs)
{
	lnum = lnum;
	dbg_scan("stop scanning LEB %d at offset %d", lnum, offs);
	ubifs_assert(offs % c->min_io_size == 0);

	sleb->endpt = ALIGN(offs, c->min_io_size);
}