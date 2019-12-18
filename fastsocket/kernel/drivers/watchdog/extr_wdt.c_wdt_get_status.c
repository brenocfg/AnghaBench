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
 unsigned char WDC_SR_FANGOOD ; 
 unsigned char WDC_SR_ISII1 ; 
 unsigned char WDC_SR_ISOI0 ; 
 unsigned char WDC_SR_PSUOVER ; 
 unsigned char WDC_SR_PSUUNDR ; 
 unsigned char WDC_SR_TGOOD ; 
 int WDIOF_EXTERN1 ; 
 int WDIOF_EXTERN2 ; 
 int WDIOF_FANFAULT ; 
 int WDIOF_OVERHEAT ; 
 int WDIOF_POWEROVER ; 
 int WDIOF_POWERUNDER ; 
 int /*<<< orphan*/  WDT_SR ; 
 unsigned char inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tachometer ; 
 int type ; 
 int /*<<< orphan*/  wdt_lock ; 

__attribute__((used)) static int wdt_get_status(void)
{
	unsigned char new_status;
	int status = 0;
	unsigned long flags;

	spin_lock_irqsave(&wdt_lock, flags);
	new_status = inb_p(WDT_SR);
	spin_unlock_irqrestore(&wdt_lock, flags);

	if (new_status & WDC_SR_ISOI0)
		status |= WDIOF_EXTERN1;
	if (new_status & WDC_SR_ISII1)
		status |= WDIOF_EXTERN2;
	if (type == 501) {
		if (!(new_status & WDC_SR_TGOOD))
			status |= WDIOF_OVERHEAT;
		if (!(new_status & WDC_SR_PSUOVER))
			status |= WDIOF_POWEROVER;
		if (!(new_status & WDC_SR_PSUUNDR))
			status |= WDIOF_POWERUNDER;
		if (tachometer) {
			if (!(new_status & WDC_SR_FANGOOD))
				status |= WDIOF_FANFAULT;
		}
	}
	return status;
}