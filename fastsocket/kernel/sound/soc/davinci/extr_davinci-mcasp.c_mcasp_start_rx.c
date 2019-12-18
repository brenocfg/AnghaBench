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
struct davinci_audio_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MCASP_GBLCTLR_REG ; 
 scalar_t__ DAVINCI_MCASP_RXBUF_REG ; 
 int /*<<< orphan*/  RXCLKRST ; 
 int /*<<< orphan*/  RXFSRST ; 
 int /*<<< orphan*/  RXHCLKRST ; 
 int /*<<< orphan*/  RXSERCLR ; 
 int /*<<< orphan*/  RXSMRST ; 
 int /*<<< orphan*/  mcasp_set_ctl_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_reg (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcasp_start_rx(struct davinci_audio_dev *dev)
{
	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLR_REG, RXHCLKRST);
	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLR_REG, RXCLKRST);
	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLR_REG, RXSERCLR);
	mcasp_set_reg(dev->base + DAVINCI_MCASP_RXBUF_REG, 0);

	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLR_REG, RXSMRST);
	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLR_REG, RXFSRST);
	mcasp_set_reg(dev->base + DAVINCI_MCASP_RXBUF_REG, 0);

	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLR_REG, RXSMRST);
	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLR_REG, RXFSRST);
}