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
struct msm_rpc_endpoint {int /*<<< orphan*/  read_q_lock; int /*<<< orphan*/  read_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int ept_packet_available(struct msm_rpc_endpoint *ept)
{
	unsigned long flags;
	int ret;
	spin_lock_irqsave(&ept->read_q_lock, flags);
	ret = !list_empty(&ept->read_q);
	spin_unlock_irqrestore(&ept->read_q_lock, flags);
	return ret;
}