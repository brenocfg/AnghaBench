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
typedef  size_t u8 ;
typedef  int u32 ;
struct davinci_audio_dev {size_t num_serializer; scalar_t__* serial_dir; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MCASP_GBLCTLX_REG ; 
 scalar_t__ DAVINCI_MCASP_TXBUF_REG ; 
 scalar_t__ DAVINCI_MCASP_XRSRCTL_REG (size_t) ; 
 int /*<<< orphan*/  TXCLKRST ; 
 int /*<<< orphan*/  TXFSRST ; 
 int /*<<< orphan*/  TXHCLKRST ; 
 int /*<<< orphan*/  TXSERCLR ; 
 int /*<<< orphan*/  TXSMRST ; 
 int TXSTATE ; 
 scalar_t__ TX_MODE ; 
 int mcasp_get_reg (scalar_t__) ; 
 int /*<<< orphan*/  mcasp_set_ctl_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcasp_set_reg (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcasp_start_tx(struct davinci_audio_dev *dev)
{
	u8 offset = 0, i;
	u32 cnt;

	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLX_REG, TXHCLKRST);
	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLX_REG, TXCLKRST);
	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLX_REG, TXSERCLR);
	mcasp_set_reg(dev->base + DAVINCI_MCASP_TXBUF_REG, 0);

	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLX_REG, TXSMRST);
	mcasp_set_ctl_reg(dev->base + DAVINCI_MCASP_GBLCTLX_REG, TXFSRST);
	mcasp_set_reg(dev->base + DAVINCI_MCASP_TXBUF_REG, 0);
	for (i = 0; i < dev->num_serializer; i++) {
		if (dev->serial_dir[i] == TX_MODE) {
			offset = i;
			break;
		}
	}

	/* wait for TX ready */
	cnt = 0;
	while (!(mcasp_get_reg(dev->base + DAVINCI_MCASP_XRSRCTL_REG(offset)) &
		 TXSTATE) && (cnt < 100000))
		cnt++;

	mcasp_set_reg(dev->base + DAVINCI_MCASP_TXBUF_REG, 0);
}