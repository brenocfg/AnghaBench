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
typedef  int u32 ;
struct pxa_camera_dev {unsigned long mclk; unsigned long ciclk; int platform_flags; int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int PXA_CAMERA_MCLK_EN ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,unsigned long) ; 

__attribute__((used)) static u32 mclk_get_divisor(struct platform_device *pdev,
			    struct pxa_camera_dev *pcdev)
{
	unsigned long mclk = pcdev->mclk;
	struct device *dev = &pdev->dev;
	u32 div;
	unsigned long lcdclk;

	lcdclk = clk_get_rate(pcdev->clk);
	pcdev->ciclk = lcdclk;

	/* mclk <= ciclk / 4 (27.4.2) */
	if (mclk > lcdclk / 4) {
		mclk = lcdclk / 4;
		dev_warn(dev, "Limiting master clock to %lu\n", mclk);
	}

	/* We verify mclk != 0, so if anyone breaks it, here comes their Oops */
	div = (lcdclk + 2 * mclk - 1) / (2 * mclk) - 1;

	/* If we're not supplying MCLK, leave it at 0 */
	if (pcdev->platform_flags & PXA_CAMERA_MCLK_EN)
		pcdev->mclk = lcdclk / (2 * (div + 1));

	dev_dbg(dev, "LCD clock %luHz, target freq %luHz, divisor %u\n",
		lcdclk, mclk, div);

	return div;
}