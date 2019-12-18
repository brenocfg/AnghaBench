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
struct pxa_camera_dev {int platform_flags; int mclk_divisor; int mclk; int /*<<< orphan*/  clk; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CICR0 ; 
 scalar_t__ CICR4 ; 
 int CICR4_HSP ; 
 int CICR4_MCLK_EN ; 
 int CICR4_PCLK_EN ; 
 int CICR4_PCP ; 
 int CICR4_VSP ; 
 int PXA_CAMERA_HSP ; 
 int PXA_CAMERA_MCLK_EN ; 
 int PXA_CAMERA_PCLK_EN ; 
 int PXA_CAMERA_PCP ; 
 int PXA_CAMERA_VSP ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recalculate_fifo_timeout (struct pxa_camera_dev*,int) ; 

__attribute__((used)) static void pxa_camera_activate(struct pxa_camera_dev *pcdev)
{
	u32 cicr4 = 0;

	/* disable all interrupts */
	__raw_writel(0x3ff, pcdev->base + CICR0);

	if (pcdev->platform_flags & PXA_CAMERA_PCLK_EN)
		cicr4 |= CICR4_PCLK_EN;
	if (pcdev->platform_flags & PXA_CAMERA_MCLK_EN)
		cicr4 |= CICR4_MCLK_EN;
	if (pcdev->platform_flags & PXA_CAMERA_PCP)
		cicr4 |= CICR4_PCP;
	if (pcdev->platform_flags & PXA_CAMERA_HSP)
		cicr4 |= CICR4_HSP;
	if (pcdev->platform_flags & PXA_CAMERA_VSP)
		cicr4 |= CICR4_VSP;

	__raw_writel(pcdev->mclk_divisor | cicr4, pcdev->base + CICR4);

	if (pcdev->platform_flags & PXA_CAMERA_MCLK_EN)
		/* Initialise the timeout under the assumption pclk = mclk */
		recalculate_fifo_timeout(pcdev, pcdev->mclk);
	else
		/* "Safe default" - 13MHz */
		recalculate_fifo_timeout(pcdev, 13000000);

	clk_enable(pcdev->clk);
}