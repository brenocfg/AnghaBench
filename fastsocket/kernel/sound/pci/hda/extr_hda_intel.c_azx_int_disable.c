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
struct azx_dev {int dummy; } ;
struct azx {int num_streams; struct azx_dev* azx_dev; } ;

/* Variables and functions */
 int ICH6_INT_CTRL_EN ; 
 int ICH6_INT_GLOBAL_EN ; 
 int /*<<< orphan*/  INTCTL ; 
 int /*<<< orphan*/  SD_CTL ; 
 int SD_INT_MASK ; 
 int azx_readl (struct azx*,int /*<<< orphan*/ ) ; 
 int azx_sd_readb (struct azx_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  azx_sd_writeb (struct azx_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  azx_writeb (struct azx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  azx_writel (struct azx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void azx_int_disable(struct azx *chip)
{
	int i;

	/* disable interrupts in stream descriptor */
	for (i = 0; i < chip->num_streams; i++) {
		struct azx_dev *azx_dev = &chip->azx_dev[i];
		azx_sd_writeb(azx_dev, SD_CTL,
			      azx_sd_readb(azx_dev, SD_CTL) & ~SD_INT_MASK);
	}

	/* disable SIE for all streams */
	azx_writeb(chip, INTCTL, 0);

	/* disable controller CIE and GIE */
	azx_writel(chip, INTCTL, azx_readl(chip, INTCTL) &
		   ~(ICH6_INT_CTRL_EN | ICH6_INT_GLOBAL_EN));
}