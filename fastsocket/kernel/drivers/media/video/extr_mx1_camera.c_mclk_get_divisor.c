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
struct mx1_camera_dev {unsigned int mclk; TYPE_2__* icd; int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned int,unsigned long) ; 

__attribute__((used)) static int mclk_get_divisor(struct mx1_camera_dev *pcdev)
{
	unsigned int mclk = pcdev->mclk;
	unsigned long div;
	unsigned long lcdclk;

	lcdclk = clk_get_rate(pcdev->clk);

	/* We verify platform_mclk_10khz != 0, so if anyone breaks it, here
	 * they get a nice Oops */
	div = (lcdclk + 2 * mclk - 1) / (2 * mclk) - 1;

	dev_dbg(pcdev->icd->dev.parent,
		"System clock %lukHz, target freq %dkHz, divisor %lu\n",
		lcdclk / 1000, mclk / 1000, div);

	return div;
}