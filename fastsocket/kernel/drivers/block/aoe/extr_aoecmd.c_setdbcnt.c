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
struct aoetgt {int minbcnt; } ;
struct aoedev {int ntargets; int maxbcnt; int /*<<< orphan*/  aoeminor; int /*<<< orphan*/  aoemajor; struct aoetgt** targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
setdbcnt(struct aoedev *d)
{
	struct aoetgt **t, **e;
	int bcnt = 0;

	t = d->targets;
	e = t + d->ntargets;
	for (; t < e && *t; t++)
		if (bcnt == 0 || bcnt > (*t)->minbcnt)
			bcnt = (*t)->minbcnt;
	if (bcnt != d->maxbcnt) {
		d->maxbcnt = bcnt;
		pr_info("aoe: e%ld.%d: setting %d byte data frames\n",
			d->aoemajor, d->aoeminor, bcnt);
	}
}