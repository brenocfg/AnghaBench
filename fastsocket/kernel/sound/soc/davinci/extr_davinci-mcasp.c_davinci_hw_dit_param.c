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
 int ACLKXE ; 
 int AFSX ; 
 int AFSXE ; 
 int AHCLKXDIV (int) ; 
 scalar_t__ DAVINCI_MCASP_ACLKXCTL_REG ; 
 scalar_t__ DAVINCI_MCASP_AHCLKXCTL_REG ; 
 scalar_t__ DAVINCI_MCASP_PDIR_REG ; 
 scalar_t__ DAVINCI_MCASP_TXDITCTL_REG ; 
 scalar_t__ DAVINCI_MCASP_TXFMCTL_REG ; 
 scalar_t__ DAVINCI_MCASP_TXFMT_REG ; 
 scalar_t__ DAVINCI_MCASP_TXMASK_REG ; 
 scalar_t__ DAVINCI_MCASP_TXTDM_REG ; 
 scalar_t__ DAVINCI_MCASP_XEVTCTL_REG ; 
 int DITEN ; 
 int FSXMOD (int) ; 
 int /*<<< orphan*/  TXDATADMADIS ; 
 int TXROT (int) ; 
 int TXSSZ (int) ; 
 int TX_ASYNC ; 
 int /*<<< orphan*/  mcasp_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_bits (scalar_t__,int) ; 
 int /*<<< orphan*/  mcasp_set_reg (scalar_t__,int) ; 

__attribute__((used)) static void davinci_hw_dit_param(struct davinci_audio_dev *dev)
{
	/* Set the PDIR for Serialiser as output */
	mcasp_set_bits(dev->base + DAVINCI_MCASP_PDIR_REG, AFSX);

	/* TXMASK for 24 bits */
	mcasp_set_reg(dev->base + DAVINCI_MCASP_TXMASK_REG, 0x00FFFFFF);

	/* Set the TX format : 24 bit right rotation, 32 bit slot, Pad 0
	   and LSB first */
	mcasp_set_bits(dev->base + DAVINCI_MCASP_TXFMT_REG,
						TXROT(6) | TXSSZ(15));

	/* Set TX frame synch : DIT Mode, 1 bit width, internal, rising edge */
	mcasp_set_reg(dev->base + DAVINCI_MCASP_TXFMCTL_REG,
						AFSXE | FSXMOD(0x180));

	/* Set the TX tdm : for all the slots */
	mcasp_set_reg(dev->base + DAVINCI_MCASP_TXTDM_REG, 0xFFFFFFFF);

	/* Set the TX clock controls : div = 1 and internal */
	mcasp_set_bits(dev->base + DAVINCI_MCASP_ACLKXCTL_REG,
						ACLKXE | TX_ASYNC);

	mcasp_clr_bits(dev->base + DAVINCI_MCASP_XEVTCTL_REG, TXDATADMADIS);

	/* Only 44100 and 48000 are valid, both have the same setting */
	mcasp_set_bits(dev->base + DAVINCI_MCASP_AHCLKXCTL_REG, AHCLKXDIV(3));

	/* Enable the DIT */
	mcasp_set_bits(dev->base + DAVINCI_MCASP_TXDITCTL_REG, DITEN);
}