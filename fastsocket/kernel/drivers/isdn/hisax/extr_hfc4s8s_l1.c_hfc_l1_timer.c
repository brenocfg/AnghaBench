#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_5__ {int /*<<< orphan*/  (* l1l2 ) (TYPE_2__*,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {TYPE_2__ ifc; } ;
struct hfc4s8s_l1 {int l1_state; int st_num; int /*<<< orphan*/  lock; int /*<<< orphan*/  hw; TYPE_1__ d_if; scalar_t__ nt_mode; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ST_WR_STA ; 
 int INDICATION ; 
 int PH_DEACTIVATE ; 
 int /*<<< orphan*/  R_ST_SEL ; 
 int /*<<< orphan*/  Write_hfc8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hfc_l1_timer(struct hfc4s8s_l1 *l1)
{
	u_long flags;

	if (!l1->enabled)
		return;

	spin_lock_irqsave(&l1->lock, flags);
	if (l1->nt_mode) {
		l1->l1_state = 1;
		Write_hfc8(l1->hw, R_ST_SEL, l1->st_num);
		Write_hfc8(l1->hw, A_ST_WR_STA, 0x11);
		spin_unlock_irqrestore(&l1->lock, flags);
		l1->d_if.ifc.l1l2(&l1->d_if.ifc,
				  PH_DEACTIVATE | INDICATION, NULL);
		spin_lock_irqsave(&l1->lock, flags);
		l1->l1_state = 1;
		Write_hfc8(l1->hw, A_ST_WR_STA, 0x1);
		spin_unlock_irqrestore(&l1->lock, flags);
	} else {
		/* activation timed out */
		Write_hfc8(l1->hw, R_ST_SEL, l1->st_num);
		Write_hfc8(l1->hw, A_ST_WR_STA, 0x13);
		spin_unlock_irqrestore(&l1->lock, flags);
		l1->d_if.ifc.l1l2(&l1->d_if.ifc,
				  PH_DEACTIVATE | INDICATION, NULL);
		spin_lock_irqsave(&l1->lock, flags);
		Write_hfc8(l1->hw, R_ST_SEL, l1->st_num);
		Write_hfc8(l1->hw, A_ST_WR_STA, 0x3);
		spin_unlock_irqrestore(&l1->lock, flags);
	}
}