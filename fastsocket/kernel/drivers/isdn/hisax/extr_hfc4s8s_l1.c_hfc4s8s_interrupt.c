#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int r_irq_ctrl; int volatile r_irq_statech; int volatile r_irqmsk_statchg; int timer_irq; int r_irq_oview; int* r_irq_fifo_blx; } ;
struct TYPE_7__ {int /*<<< orphan*/  tqueue; TYPE_1__ mr; int /*<<< orphan*/  fifo_sched_cnt; } ;
typedef  TYPE_2__ hfc4s8s_hw ;

/* Variables and functions */
 int GetRegAddr (TYPE_2__*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int volatile M_FR_IRQSTA ; 
 int M_GLOB_IRQ_EN ; 
 int volatile M_MISC_IRQSTA ; 
 int M_TI_IRQ ; 
 int R_IRQ_FIFO_BL0 ; 
 int R_IRQ_MISC ; 
 int R_IRQ_OVIEW ; 
 int R_SCI ; 
 int R_STATUS ; 
 int volatile Read_hfc8 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SetRegAddr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
hfc4s8s_interrupt(int intno, void *dev_id)
{
	hfc4s8s_hw *hw = dev_id;
	u_char b, ovr;
	volatile u_char *ovp;
	int idx;
	u_char old_ioreg;

	if (!hw || !(hw->mr.r_irq_ctrl & M_GLOB_IRQ_EN))
		return IRQ_NONE;

#ifndef	HISAX_HFC4S8S_PCIMEM
	/* read current selected regsister */
	old_ioreg = GetRegAddr(hw);
#endif

	/* Layer 1 State change */
	hw->mr.r_irq_statech |=
	    (Read_hfc8(hw, R_SCI) & hw->mr.r_irqmsk_statchg);
	if (!
	    (b = (Read_hfc8(hw, R_STATUS) & (M_MISC_IRQSTA | M_FR_IRQSTA)))
&& !hw->mr.r_irq_statech) {
#ifndef	HISAX_HFC4S8S_PCIMEM
		SetRegAddr(hw, old_ioreg);
#endif
		return IRQ_NONE;
	}

	/* timer event */
	if (Read_hfc8(hw, R_IRQ_MISC) & M_TI_IRQ) {
		hw->mr.timer_irq = 1;
		hw->fifo_sched_cnt--;
	}

	/* FIFO event */
	if ((ovr = Read_hfc8(hw, R_IRQ_OVIEW))) {
		hw->mr.r_irq_oview |= ovr;
		idx = R_IRQ_FIFO_BL0;
		ovp = hw->mr.r_irq_fifo_blx;
		while (ovr) {
			if ((ovr & 1)) {
				*ovp |= Read_hfc8(hw, idx);
			}
			ovp++;
			idx++;
			ovr >>= 1;
		}
	}

	/* queue the request to allow other cards to interrupt */
	schedule_work(&hw->tqueue);

#ifndef	HISAX_HFC4S8S_PCIMEM
	SetRegAddr(hw, old_ioreg);
#endif
	return IRQ_HANDLED;
}