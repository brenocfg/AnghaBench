#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nes_cm_node {int accelerated; TYPE_1__* listener; scalar_t__ accept_pend; } ;
struct TYPE_5__ {scalar_t__ expires; } ;
struct nes_cm_core {TYPE_2__ tcp_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  pend_accepts_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ NES_SHORT_TIME ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_pending (TYPE_2__*) ; 

__attribute__((used)) static inline int mini_cm_accelerated(struct nes_cm_core *cm_core,
				      struct nes_cm_node *cm_node)
{
	u32 was_timer_set;

	cm_node->accelerated = 1;

	if (cm_node->accept_pend) {
		BUG_ON(!cm_node->listener);
		atomic_dec(&cm_node->listener->pend_accepts_cnt);
		cm_node->accept_pend = 0;
		BUG_ON(atomic_read(&cm_node->listener->pend_accepts_cnt) < 0);
	}

	was_timer_set = timer_pending(&cm_core->tcp_timer);
	if (!was_timer_set) {
		cm_core->tcp_timer.expires = jiffies + NES_SHORT_TIME;
		add_timer(&cm_core->tcp_timer);
	}

	return 0;
}