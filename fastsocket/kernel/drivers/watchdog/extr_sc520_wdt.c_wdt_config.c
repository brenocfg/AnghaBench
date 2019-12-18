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
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wdt_spinlock ; 
 int /*<<< orphan*/  wdtmrctl ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wdt_config(int writeval)
{
	__u16 dummy;
	unsigned long flags;

	/* buy some time (ping) */
	spin_lock_irqsave(&wdt_spinlock, flags);
	dummy = readw(wdtmrctl);	/* ensure write synchronization */
	writew(0xAAAA, wdtmrctl);
	writew(0x5555, wdtmrctl);
	/* unlock WDT = make WDT configuration register writable one time */
	writew(0x3333, wdtmrctl);
	writew(0xCCCC, wdtmrctl);
	/* write WDT configuration register */
	writew(writeval, wdtmrctl);
	spin_unlock_irqrestore(&wdt_spinlock, flags);
}