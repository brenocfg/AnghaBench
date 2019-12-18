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
struct ubifs_info {int lpt_first; int lpt_last; TYPE_1__* ltab; } ;
struct TYPE_2__ {int dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_lp (char*,int,int,int) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 

void ubifs_add_lpt_dirt(struct ubifs_info *c, int lnum, int dirty)
{
	if (!dirty || !lnum)
		return;
	dbg_lp("LEB %d add %d to %d",
	       lnum, dirty, c->ltab[lnum - c->lpt_first].dirty);
	ubifs_assert(lnum >= c->lpt_first && lnum <= c->lpt_last);
	c->ltab[lnum - c->lpt_first].dirty += dirty;
}