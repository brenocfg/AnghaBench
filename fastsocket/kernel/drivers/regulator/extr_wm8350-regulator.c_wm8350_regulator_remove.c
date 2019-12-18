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
struct wm8350 {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct platform_device {size_t id; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct regulator_dev* platform_get_drvdata (struct platform_device*) ; 
 struct wm8350* rdev_get_drvdata (struct regulator_dev*) ; 
 int /*<<< orphan*/  regulator_unregister (struct regulator_dev*) ; 
 int /*<<< orphan*/  wm8350_free_irq (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_mask_irq (struct wm8350*,int /*<<< orphan*/ ) ; 
 TYPE_1__* wm8350_reg ; 

__attribute__((used)) static int wm8350_regulator_remove(struct platform_device *pdev)
{
	struct regulator_dev *rdev = platform_get_drvdata(pdev);
	struct wm8350 *wm8350 = rdev_get_drvdata(rdev);

	wm8350_mask_irq(wm8350, wm8350_reg[pdev->id].irq);
	wm8350_free_irq(wm8350, wm8350_reg[pdev->id].irq);

	regulator_unregister(rdev);

	return 0;
}