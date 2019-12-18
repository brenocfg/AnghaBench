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
struct ib_mad_port_private {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; int /*<<< orphan*/  port_list; } ;
struct ib_cq {struct ib_mad_port_private* cq_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_mad_port_list_lock ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ib_mad_thread_completion_handler(struct ib_cq *cq, void *arg)
{
	struct ib_mad_port_private *port_priv = cq->cq_context;
	unsigned long flags;

	spin_lock_irqsave(&ib_mad_port_list_lock, flags);
	if (!list_empty(&port_priv->port_list))
		queue_work(port_priv->wq, &port_priv->work);
	spin_unlock_irqrestore(&ib_mad_port_list_lock, flags);
}