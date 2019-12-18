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
struct ubifs_info {int lpt_lebs; int lpt_first; int nhead_lnum; scalar_t__ leb_size; int /*<<< orphan*/  lp_mutex; TYPE_1__* ltab; } ;
struct TYPE_2__ {scalar_t__ free; int dirty; int /*<<< orphan*/  tgc; } ;

/* Variables and functions */
 int ENOSPC ; 
 int lpt_gc_lnum (struct ubifs_info*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 

__attribute__((used)) static int lpt_gc(struct ubifs_info *c)
{
	int i, lnum = -1, dirty = 0;

	mutex_lock(&c->lp_mutex);
	for (i = 0; i < c->lpt_lebs; i++) {
		ubifs_assert(!c->ltab[i].tgc);
		if (i + c->lpt_first == c->nhead_lnum ||
		    c->ltab[i].free + c->ltab[i].dirty == c->leb_size)
			continue;
		if (c->ltab[i].dirty > dirty) {
			dirty = c->ltab[i].dirty;
			lnum = i + c->lpt_first;
		}
	}
	mutex_unlock(&c->lp_mutex);
	if (lnum == -1)
		return -ENOSPC;
	return lpt_gc_lnum(c, lnum);
}