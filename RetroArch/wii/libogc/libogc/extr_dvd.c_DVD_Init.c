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
 int /*<<< orphan*/  IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PI_DI ; 
 int /*<<< orphan*/  IRQ_Request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWP_InitQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_CreateAlarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __DVDInitWA () ; 
 int /*<<< orphan*/  __DVDInterruptHandler ; 
 int /*<<< orphan*/  __UnmaskIrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_clearwaitingqueue () ; 
 int __dvd_initflag ; 
 int /*<<< orphan*/  __dvd_timeoutalarm ; 
 int /*<<< orphan*/  __dvd_wait_queue ; 

void DVD_Init()
{
	if(!__dvd_initflag) {
		__dvd_initflag = 1;
		__dvd_clearwaitingqueue();
		__DVDInitWA();

		IRQ_Request(IRQ_PI_DI,__DVDInterruptHandler,NULL);
		__UnmaskIrq(IRQMASK(IRQ_PI_DI));

		SYS_CreateAlarm(&__dvd_timeoutalarm);
		LWP_InitQueue(&__dvd_wait_queue);
	}
}