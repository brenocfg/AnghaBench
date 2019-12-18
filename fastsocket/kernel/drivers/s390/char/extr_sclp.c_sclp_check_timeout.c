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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCLP_REQ_FAILED ; 
 TYPE_1__ sclp_init_req ; 
 int /*<<< orphan*/  sclp_lock ; 
 scalar_t__ sclp_running_state ; 
 scalar_t__ sclp_running_state_idle ; 
 scalar_t__ sclp_running_state_running ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
sclp_check_timeout(unsigned long data)
{
	unsigned long flags;

	spin_lock_irqsave(&sclp_lock, flags);
	if (sclp_running_state == sclp_running_state_running) {
		sclp_init_req.status = SCLP_REQ_FAILED;
		sclp_running_state = sclp_running_state_idle;
	}
	spin_unlock_irqrestore(&sclp_lock, flags);
}