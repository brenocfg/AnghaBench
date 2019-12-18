#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ addr; int /*<<< orphan*/  cmds; scalar_t__ rp; scalar_t__ wp; int /*<<< orphan*/ * buf; } ;
struct TYPE_5__ {scalar_t__ area; scalar_t__ addr; } ;
struct TYPE_4__ {scalar_t__ addr; int /*<<< orphan*/ * buf; } ;
struct azx {int driver_caps; int /*<<< orphan*/  reg_lock; TYPE_3__ rirb; TYPE_2__ rb; TYPE_1__ corb; } ;

/* Variables and functions */
 int AZX_DCAPS_CTX_WORKAROUND ; 
 int /*<<< orphan*/  CORBCTL ; 
 int /*<<< orphan*/  CORBLBASE ; 
 int /*<<< orphan*/  CORBRP ; 
 int /*<<< orphan*/  CORBSIZE ; 
 int /*<<< orphan*/  CORBUBASE ; 
 int /*<<< orphan*/  CORBWP ; 
 int ICH6_CORBCTL_RUN ; 
 int ICH6_CORBRP_RST ; 
 int ICH6_RBCTL_DMA_EN ; 
 int ICH6_RBCTL_IRQ_EN ; 
 int ICH6_RIRBWP_RST ; 
 int /*<<< orphan*/  RINTCNT ; 
 int /*<<< orphan*/  RIRBCTL ; 
 int /*<<< orphan*/  RIRBLBASE ; 
 int /*<<< orphan*/  RIRBSIZE ; 
 int /*<<< orphan*/  RIRBUBASE ; 
 int /*<<< orphan*/  RIRBWP ; 
 int /*<<< orphan*/  azx_writeb (struct azx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  azx_writel (struct azx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  azx_writew (struct azx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void azx_init_cmd_io(struct azx *chip)
{
	spin_lock_irq(&chip->reg_lock);
	/* CORB set up */
	chip->corb.addr = chip->rb.addr;
	chip->corb.buf = (u32 *)chip->rb.area;
	azx_writel(chip, CORBLBASE, (u32)chip->corb.addr);
	azx_writel(chip, CORBUBASE, upper_32_bits(chip->corb.addr));

	/* set the corb size to 256 entries (ULI requires explicitly) */
	azx_writeb(chip, CORBSIZE, 0x02);
	/* set the corb write pointer to 0 */
	azx_writew(chip, CORBWP, 0);
	/* reset the corb hw read pointer */
	azx_writew(chip, CORBRP, ICH6_CORBRP_RST);
	/* enable corb dma */
	azx_writeb(chip, CORBCTL, ICH6_CORBCTL_RUN);

	/* RIRB set up */
	chip->rirb.addr = chip->rb.addr + 2048;
	chip->rirb.buf = (u32 *)(chip->rb.area + 2048);
	chip->rirb.wp = chip->rirb.rp = 0;
	memset(chip->rirb.cmds, 0, sizeof(chip->rirb.cmds));
	azx_writel(chip, RIRBLBASE, (u32)chip->rirb.addr);
	azx_writel(chip, RIRBUBASE, upper_32_bits(chip->rirb.addr));

	/* set the rirb size to 256 entries (ULI requires explicitly) */
	azx_writeb(chip, RIRBSIZE, 0x02);
	/* reset the rirb hw write pointer */
	azx_writew(chip, RIRBWP, ICH6_RIRBWP_RST);
	/* set N=1, get RIRB response interrupt for new entry */
	if (chip->driver_caps & AZX_DCAPS_CTX_WORKAROUND)
		azx_writew(chip, RINTCNT, 0xc0);
	else
		azx_writew(chip, RINTCNT, 1);
	/* enable rirb dma and response irq */
	azx_writeb(chip, RIRBCTL, ICH6_RBCTL_DMA_EN | ICH6_RBCTL_IRQ_EN);
	spin_unlock_irq(&chip->reg_lock);
}