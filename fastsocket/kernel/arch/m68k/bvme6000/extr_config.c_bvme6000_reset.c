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
struct TYPE_2__ {int pcddr; } ;
typedef  TYPE_1__* PitRegsPtr ;

/* Variables and functions */
 int /*<<< orphan*/  BVME_PIT_BASE ; 
 int /*<<< orphan*/  printk (char*) ; 

void bvme6000_reset(void)
{
	volatile PitRegsPtr pit = (PitRegsPtr)BVME_PIT_BASE;

	printk ("\r\n\nCalled bvme6000_reset\r\n"
			"\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r\r");
	/* The string of returns is to delay the reset until the whole
	 * message is output. */
	/* Enable the watchdog, via PIT port C bit 4 */

	pit->pcddr	|= 0x10;	/* WDOG enable */

	while(1)
		;
}