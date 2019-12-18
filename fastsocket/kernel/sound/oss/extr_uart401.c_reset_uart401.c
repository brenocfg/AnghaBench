#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ input_byte; } ;
typedef  TYPE_1__ uart401_devc ;

/* Variables and functions */
 int /*<<< orphan*/  DDB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 scalar_t__ MPU_ACK ; 
 int /*<<< orphan*/  MPU_RESET ; 
 scalar_t__ input_avail (TYPE_1__*) ; 
 int /*<<< orphan*/  output_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  uart401_cmd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart401_input_loop (TYPE_1__*) ; 
 scalar_t__ uart401_read (TYPE_1__*) ; 

__attribute__((used)) static int reset_uart401(uart401_devc * devc)
{
	int ok, timeout, n;

	/*
	 * Send the RESET command. Try again if no success at the first time.
	 */

	ok = 0;

	for (n = 0; n < 2 && !ok; n++)
	{
		for (timeout = 30000; timeout > 0 && !output_ready(devc); timeout--);
		devc->input_byte = 0;
		uart401_cmd(devc, MPU_RESET);

		/*
		 * Wait at least 25 msec. This method is not accurate so let's make the
		 * loop bit longer. Cannot sleep since this is called during boot.
		 */

		for (timeout = 50000; timeout > 0 && !ok; timeout--)
		{
			if (devc->input_byte == MPU_ACK)	/* Interrupt */
				ok = 1;
			else if (input_avail(devc))
			{
				if (uart401_read(devc) == MPU_ACK)
					ok = 1;
			}
		}
	}


	if (ok)
	{
		DEB(printk("Reset UART401 OK\n"));
	}
	else
		DDB(printk("Reset UART401 failed - No hardware detected.\n"));

	if (ok)
		uart401_input_loop(devc);	/*
						 * Flush input before enabling interrupts
						 */

	return ok;
}