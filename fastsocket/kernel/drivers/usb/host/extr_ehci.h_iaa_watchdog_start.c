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
struct ehci_hcd {int /*<<< orphan*/  iaa_watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_IAA_MSECS ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
iaa_watchdog_start(struct ehci_hcd *ehci)
{
	WARN_ON(timer_pending(&ehci->iaa_watchdog));
	mod_timer(&ehci->iaa_watchdog,
			jiffies + msecs_to_jiffies(EHCI_IAA_MSECS));
}