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
struct mx1_camera_dev {scalar_t__ base; int /*<<< orphan*/  clk; TYPE_2__* icd; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ CSICR1 ; 
 unsigned int CSICR1_EN ; 
 unsigned int CSICR1_FCC ; 
 unsigned int CSICR1_GCLK_MODE ; 
 unsigned int CSICR1_MCLKDIV (int /*<<< orphan*/ ) ; 
 unsigned int CSICR1_MCLKEN ; 
 unsigned int CSICR1_RXFF_LEVEL (int) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mclk_get_divisor (struct mx1_camera_dev*) ; 

__attribute__((used)) static void mx1_camera_activate(struct mx1_camera_dev *pcdev)
{
	unsigned int csicr1 = CSICR1_EN;

	dev_dbg(pcdev->icd->dev.parent, "Activate device\n");

	clk_enable(pcdev->clk);

	/* enable CSI before doing anything else */
	__raw_writel(csicr1, pcdev->base + CSICR1);

	csicr1 |= CSICR1_MCLKEN | CSICR1_FCC | CSICR1_GCLK_MODE;
	csicr1 |= CSICR1_MCLKDIV(mclk_get_divisor(pcdev));
	csicr1 |= CSICR1_RXFF_LEVEL(2); /* 16 words */

	__raw_writel(csicr1, pcdev->base + CSICR1);
}