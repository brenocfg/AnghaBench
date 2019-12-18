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
typedef  scalar_t__ ulong ;
struct TYPE_3__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int line; int /*<<< orphan*/  irq; int /*<<< orphan*/ * ops; scalar_t__ mapbase; scalar_t__ membase; int /*<<< orphan*/  fifosize; int /*<<< orphan*/  type; int /*<<< orphan*/  iotype; int /*<<< orphan*/  uartclk; } ;
struct mpsc_port_info {TYPE_2__ port; int /*<<< orphan*/ * shared_regs; int /*<<< orphan*/  BRG_BCR_m; int /*<<< orphan*/  MPSC_MPCR_m; int /*<<< orphan*/  MPSC_CHR_10_m; int /*<<< orphan*/  MPSC_CHR_2_m; int /*<<< orphan*/  MPSC_CHR_1_m; int /*<<< orphan*/  default_flow; int /*<<< orphan*/  default_parity; int /*<<< orphan*/  default_bits; int /*<<< orphan*/  default_baud; int /*<<< orphan*/  mpsc_max_idle; int /*<<< orphan*/  brg_clk_src; int /*<<< orphan*/  brg_can_tune; int /*<<< orphan*/  cache_mgmt; int /*<<< orphan*/  mirror_regs; scalar_t__ mpsc_base; } ;
struct mpsc_pdata {int /*<<< orphan*/  bcr_val; int /*<<< orphan*/  mpcr_val; int /*<<< orphan*/  chr_10_val; int /*<<< orphan*/  chr_2_val; int /*<<< orphan*/  chr_1_val; int /*<<< orphan*/  default_flow; int /*<<< orphan*/  default_parity; int /*<<< orphan*/  default_bits; int /*<<< orphan*/  default_baud; int /*<<< orphan*/  max_idle; int /*<<< orphan*/  brg_clk_src; int /*<<< orphan*/  brg_can_tune; int /*<<< orphan*/  cache_mgmt; int /*<<< orphan*/  mirror_regs; int /*<<< orphan*/  brg_clk_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPSC_TXBE_SIZE ; 
 int /*<<< orphan*/  PORT_MPSC ; 
 int /*<<< orphan*/  UPIO_MEM ; 
 int /*<<< orphan*/  mpsc_pops ; 
 int /*<<< orphan*/  mpsc_shared_regs ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpsc_drv_get_platform_data(struct mpsc_port_info *pi,
		struct platform_device *pd, int num)
{
	struct mpsc_pdata	*pdata;

	pdata = (struct mpsc_pdata *)pd->dev.platform_data;

	pi->port.uartclk = pdata->brg_clk_freq;
	pi->port.iotype = UPIO_MEM;
	pi->port.line = num;
	pi->port.type = PORT_MPSC;
	pi->port.fifosize = MPSC_TXBE_SIZE;
	pi->port.membase = pi->mpsc_base;
	pi->port.mapbase = (ulong)pi->mpsc_base;
	pi->port.ops = &mpsc_pops;

	pi->mirror_regs = pdata->mirror_regs;
	pi->cache_mgmt = pdata->cache_mgmt;
	pi->brg_can_tune = pdata->brg_can_tune;
	pi->brg_clk_src = pdata->brg_clk_src;
	pi->mpsc_max_idle = pdata->max_idle;
	pi->default_baud = pdata->default_baud;
	pi->default_bits = pdata->default_bits;
	pi->default_parity = pdata->default_parity;
	pi->default_flow = pdata->default_flow;

	/* Initial values of mirrored regs */
	pi->MPSC_CHR_1_m = pdata->chr_1_val;
	pi->MPSC_CHR_2_m = pdata->chr_2_val;
	pi->MPSC_CHR_10_m = pdata->chr_10_val;
	pi->MPSC_MPCR_m = pdata->mpcr_val;
	pi->BRG_BCR_m = pdata->bcr_val;

	pi->shared_regs = &mpsc_shared_regs;

	pi->port.irq = platform_get_irq(pd, 0);
}