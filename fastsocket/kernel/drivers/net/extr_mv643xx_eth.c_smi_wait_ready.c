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
struct mv643xx_eth_shared_private {scalar_t__ err_interrupt; int /*<<< orphan*/  smi_busy_wait; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  smi_is_done (struct mv643xx_eth_shared_private*) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smi_wait_ready(struct mv643xx_eth_shared_private *msp)
{
	if (msp->err_interrupt == NO_IRQ) {
		int i;

		for (i = 0; !smi_is_done(msp); i++) {
			if (i == 10)
				return -ETIMEDOUT;
			msleep(10);
		}

		return 0;
	}

	if (!smi_is_done(msp)) {
		wait_event_timeout(msp->smi_busy_wait, smi_is_done(msp),
				   msecs_to_jiffies(100));
		if (!smi_is_done(msp))
			return -ETIMEDOUT;
	}

	return 0;
}