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

/* Variables and functions */
 int /*<<< orphan*/  INT_A9_M2A_0 ; 
 int /*<<< orphan*/  INT_A9_M2A_5 ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smd_irq_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsm_irq_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smd_core_init(void)
{
	int r;
	pr_info("smd_core_init()\n");

	r = request_irq(INT_A9_M2A_0, smd_irq_handler,
			IRQF_TRIGGER_RISING, "smd_dev", 0);
	if (r < 0)
		return r;
	r = enable_irq_wake(INT_A9_M2A_0);
	if (r < 0)
		pr_err("smd_core_init: enable_irq_wake failed for A9_M2A_0\n");

	r = request_irq(INT_A9_M2A_5, smsm_irq_handler,
			IRQF_TRIGGER_RISING, "smsm_dev", 0);
	if (r < 0) {
		free_irq(INT_A9_M2A_0, 0);
		return r;
	}
	r = enable_irq_wake(INT_A9_M2A_5);
	if (r < 0)
		pr_err("smd_core_init: enable_irq_wake failed for A9_M2A_5\n");

	/* we may have missed a signal while booting -- fake
	 * an interrupt to make sure we process any existing
	 * state
	 */
	smsm_irq_handler(0, 0);

	pr_info("smd_core_init() done\n");

	return 0;
}