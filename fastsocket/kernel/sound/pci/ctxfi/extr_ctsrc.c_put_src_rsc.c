#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct src_mgr {int /*<<< orphan*/  mgr_lock; int /*<<< orphan*/  mgr; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct src {scalar_t__ mode; int multi; TYPE_2__ rsc; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* index ) (TYPE_2__*) ;int /*<<< orphan*/  (* master ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ MEMRD ; 
 int /*<<< orphan*/  kfree (struct src*) ; 
 int /*<<< orphan*/  mgr_put_resource (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  src_rsc_uninit (struct src*,struct src_mgr*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

__attribute__((used)) static int put_src_rsc(struct src_mgr *mgr, struct src *src)
{
	unsigned long flags;

	spin_lock_irqsave(&mgr->mgr_lock, flags);
	src->rsc.ops->master(&src->rsc);
	if (MEMRD == src->mode)
		mgr_put_resource(&mgr->mgr, src->multi,
				 src->rsc.ops->index(&src->rsc));
	else
		mgr_put_resource(&mgr->mgr, 1, src->rsc.ops->index(&src->rsc));

	spin_unlock_irqrestore(&mgr->mgr_lock, flags);
	src_rsc_uninit(src, mgr);
	kfree(src);

	return 0;
}