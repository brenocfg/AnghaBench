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
struct ablkcipher_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_th; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int ablkcipher_enqueue_request (int /*<<< orphan*/ *,struct ablkcipher_request*) ; 
 TYPE_1__* cpg ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_handle_req(struct ablkcipher_request *req)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&cpg->lock, flags);
	ret = ablkcipher_enqueue_request(&cpg->queue, req);
	spin_unlock_irqrestore(&cpg->lock, flags);
	wake_up_process(cpg->queue_th);
	return ret;
}