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
struct sa1100fb_info {int /*<<< orphan*/  ctrlr_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  GPCR ; 
 int HZ ; 
 int /*<<< orphan*/  LCCR0 ; 
 int /*<<< orphan*/  LCCR0_LDM ; 
 int /*<<< orphan*/  LCCR0_LEN ; 
 int LCSR ; 
 int /*<<< orphan*/  SHANNON_GPIO_DISP_EN ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ machine_is_shannon () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void sa1100fb_disable_controller(struct sa1100fb_info *fbi)
{
	DECLARE_WAITQUEUE(wait, current);

	DPRINTK("Disabling LCD controller\n");

	if (machine_is_shannon()) {
		GPCR |= SHANNON_GPIO_DISP_EN;
	}	

	set_current_state(TASK_UNINTERRUPTIBLE);
	add_wait_queue(&fbi->ctrlr_wait, &wait);

	LCSR = 0xffffffff;	/* Clear LCD Status Register */
	LCCR0 &= ~LCCR0_LDM;	/* Enable LCD Disable Done Interrupt */
	LCCR0 &= ~LCCR0_LEN;	/* Disable LCD Controller */

	schedule_timeout(20 * HZ / 1000);
	remove_wait_queue(&fbi->ctrlr_wait, &wait);
}