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
struct gfs2_rgrp_list {unsigned int rl_rgrps; int /*<<< orphan*/ * rl_ghs; int /*<<< orphan*/ * rl_rgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_holder_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void gfs2_rlist_free(struct gfs2_rgrp_list *rlist)
{
	unsigned int x;

	kfree(rlist->rl_rgd);

	if (rlist->rl_ghs) {
		for (x = 0; x < rlist->rl_rgrps; x++)
			gfs2_holder_uninit(&rlist->rl_ghs[x]);
		kfree(rlist->rl_ghs);
	}
}