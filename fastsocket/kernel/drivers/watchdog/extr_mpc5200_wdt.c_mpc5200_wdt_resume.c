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
struct of_device {int /*<<< orphan*/  dev; } ;
struct mpc5200_wdt {scalar_t__ count; } ;

/* Variables and functions */
 struct mpc5200_wdt* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc5200_wdt_start (struct mpc5200_wdt*) ; 

__attribute__((used)) static int mpc5200_wdt_resume(struct of_device *op)
{
	struct mpc5200_wdt *wdt = dev_get_drvdata(&op->dev);
	if (wdt->count)
		mpc5200_wdt_start(wdt);
	return 0;
}