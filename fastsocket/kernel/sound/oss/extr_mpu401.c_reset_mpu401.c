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
struct mpu_config {int initialized; scalar_t__ uart_mode; scalar_t__ last_status; scalar_t__ m_left; scalar_t__ m_ptr; int /*<<< orphan*/  m_state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ MPU_ACK ; 
 int /*<<< orphan*/  MPU_RESET ; 
 int /*<<< orphan*/  ST_INIT ; 
 scalar_t__ input_avail (struct mpu_config*) ; 
 int output_ready (struct mpu_config*) ; 
 scalar_t__ read_data (struct mpu_config*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_command (struct mpu_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset_mpu401(struct mpu_config *devc)
{
	unsigned long flags;
	int ok, timeout, n;
	int timeout_limit;

	/*
	 * Send the RESET command. Try again if no success at the first time.
	 * (If the device is in the UART mode, it will not ack the reset cmd).
	 */

	ok = 0;

	timeout_limit = devc->initialized ? 30000 : 100000;
	devc->initialized = 1;

	for (n = 0; n < 2 && !ok; n++)
	{
		for (timeout = timeout_limit; timeout > 0 && !ok; timeout--)
			  ok = output_ready(devc);

		write_command(devc, MPU_RESET);	/*
							   * Send MPU-401 RESET Command
							 */

		/*
		 * Wait at least 25 msec. This method is not accurate so let's make the
		 * loop bit longer. Cannot sleep since this is called during boot.
		 */

		for (timeout = timeout_limit * 2; timeout > 0 && !ok; timeout--)
		{
			spin_lock_irqsave(&devc->lock,flags);
			if (input_avail(devc))
				if (read_data(devc) == MPU_ACK)
					ok = 1;
			spin_unlock_irqrestore(&devc->lock,flags);
		}

	}

	devc->m_state = ST_INIT;
	devc->m_ptr = 0;
	devc->m_left = 0;
	devc->last_status = 0;
	devc->uart_mode = 0;

	return ok;
}