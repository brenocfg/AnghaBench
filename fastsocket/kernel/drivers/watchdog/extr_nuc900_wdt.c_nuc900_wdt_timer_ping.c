#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* pdev; int /*<<< orphan*/  timer; int /*<<< orphan*/  next_heartbeat; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ WDT_TIMEOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* nuc900_wdt ; 
 int /*<<< orphan*/  nuc900_wdt_keepalive () ; 
 scalar_t__ time_before (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nuc900_wdt_timer_ping(unsigned long data)
{
	if (time_before(jiffies, nuc900_wdt->next_heartbeat)) {
		nuc900_wdt_keepalive();
		mod_timer(&nuc900_wdt->timer, jiffies + WDT_TIMEOUT);
	} else
		dev_warn(&nuc900_wdt->pdev->dev, "Will reset the machine !\n");
}