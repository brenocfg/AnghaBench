#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_9__ {scalar_t__ r_irq_ctrl; } ;
struct TYPE_7__ {int clock_mode; } ;
struct TYPE_8__ {TYPE_4__ mr; TYPE_1__ driver_data; int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ hfc4s8s_hw ;

/* Variables and functions */
 int /*<<< orphan*/  M_FZ_MD ; 
 int /*<<< orphan*/  M_PCM_CLK ; 
 int /*<<< orphan*/  M_PCM_MD ; 
 int /*<<< orphan*/  M_SRES ; 
 int /*<<< orphan*/  R_BRG_PCM_CFG ; 
 int /*<<< orphan*/  R_CIRM ; 
 int /*<<< orphan*/  R_CTRL ; 
 int /*<<< orphan*/  R_FIFO_MD ; 
 int /*<<< orphan*/  R_PCM_MD0 ; 
 int /*<<< orphan*/  R_RAM_MISC ; 
 int /*<<< orphan*/  R_TI_WD ; 
 int /*<<< orphan*/  TRANS_TIMER_MODE ; 
 int /*<<< orphan*/  Write_hfc8 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_busy (TYPE_2__*) ; 

__attribute__((used)) static void
chipreset(hfc4s8s_hw * hw)
{
	u_long flags;

	spin_lock_irqsave(&hw->lock, flags);
	Write_hfc8(hw, R_CTRL, 0);	/* use internal RAM */
	Write_hfc8(hw, R_RAM_MISC, 0);	/* 32k*8 RAM */
	Write_hfc8(hw, R_FIFO_MD, 0);	/* fifo mode 386 byte/fifo simple mode */
	Write_hfc8(hw, R_CIRM, M_SRES);	/* reset chip */
	hw->mr.r_irq_ctrl = 0;	/* interrupt is inactive */
	spin_unlock_irqrestore(&hw->lock, flags);

	udelay(3);
	Write_hfc8(hw, R_CIRM, 0);	/* disable reset */
	wait_busy(hw);

	Write_hfc8(hw, R_PCM_MD0, M_PCM_MD);	/* master mode */
	Write_hfc8(hw, R_RAM_MISC, M_FZ_MD);	/* transmit fifo option */
	if (hw->driver_data.clock_mode == 1)
		Write_hfc8(hw, R_BRG_PCM_CFG, M_PCM_CLK);	/* PCM clk / 2 */
	Write_hfc8(hw, R_TI_WD, TRANS_TIMER_MODE);	/* timer interval */

	memset(&hw->mr, 0, sizeof(hw->mr));
}