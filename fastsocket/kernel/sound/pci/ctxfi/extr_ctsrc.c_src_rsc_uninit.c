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
struct src_mgr {int /*<<< orphan*/  (* commit_write ) (struct src_mgr*) ;int /*<<< orphan*/  (* src_disable ) (struct src_mgr*,struct src*) ;} ;
struct src {scalar_t__ mode; int multi; int /*<<< orphan*/ * intlv; int /*<<< orphan*/ * ops; int /*<<< orphan*/  rsc; } ;

/* Variables and functions */
 scalar_t__ MEMRD ; 
 scalar_t__ NUM_SRCMODES ; 
 int /*<<< orphan*/  rsc_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct src_mgr*,struct src*) ; 
 int /*<<< orphan*/  stub2 (struct src_mgr*) ; 

__attribute__((used)) static int src_rsc_uninit(struct src *src, struct src_mgr *mgr)
{
	int i, n;
	struct src *p;

	n = (MEMRD == src->mode) ? src->multi : 1;
	for (i = 0, p = src; i < n; i++, p++) {
		mgr->src_disable(mgr, p);
		rsc_uninit(&p->rsc);
		p->multi = 0;
		p->ops = NULL;
		p->mode = NUM_SRCMODES;
		p->intlv = NULL;
	}
	mgr->commit_write(mgr);

	return 0;
}