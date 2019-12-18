#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct src_mgr {TYPE_1__ mgr; } ;
struct TYPE_9__ {int msr; TYPE_2__* ops; } ;
struct src {TYPE_3__ rsc; } ;
struct hw {int /*<<< orphan*/  (* src_mgr_dsb_src ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* master ) (TYPE_3__*) ;int /*<<< orphan*/  (* next_conj ) (TYPE_3__*) ;int /*<<< orphan*/  (* index ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*) ; 

__attribute__((used)) static int src_disable(struct src_mgr *mgr, struct src *src)
{
	struct hw *hw = mgr->mgr.hw;
	int i;

	src->rsc.ops->master(&src->rsc);
	for (i = 0; i < src->rsc.msr; i++) {
		hw->src_mgr_dsb_src(mgr->mgr.ctrl_blk,
				    src->rsc.ops->index(&src->rsc));
		src->rsc.ops->next_conj(&src->rsc);
	}
	src->rsc.ops->master(&src->rsc);

	return 0;
}