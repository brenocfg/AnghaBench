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
struct of_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;
struct mpc5200_wdt {TYPE_1__ mem; int /*<<< orphan*/  regs; int /*<<< orphan*/  miscdev; } ;

/* Variables and functions */
 struct mpc5200_wdt* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mpc5200_wdt*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpc5200_wdt_stop (struct mpc5200_wdt*) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mpc5200_wdt_remove(struct of_device *op)
{
	struct mpc5200_wdt *wdt = dev_get_drvdata(&op->dev);

	mpc5200_wdt_stop(wdt);
	misc_deregister(&wdt->miscdev);
	iounmap(wdt->regs);
	release_mem_region(wdt->mem.start, wdt->mem.end - wdt->mem.start + 1);
	kfree(wdt);

	return 0;
}