#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_2__ {scalar_t__ tx_idx; int /*<<< orphan*/  Flags; } ;
struct isac_hw {int /*<<< orphan*/  hwlock; int /*<<< orphan*/  name; TYPE_1__ dch; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_BUSY_TIMER ; 
 int /*<<< orphan*/  FLG_L1_BUSY ; 
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  ISAC_RBCH ; 
 int ISAC_RBCH_XAC ; 
 int /*<<< orphan*/  ISAC_STAR ; 
 int ReadISAC (struct isac_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteISAC (struct isac_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbusy_timer_handler(struct isac_hw *isac)
{
	int rbch, star;
	u_long flags;

	if (test_bit(FLG_BUSY_TIMER, &isac->dch.Flags)) {
		spin_lock_irqsave(isac->hwlock, flags);
		rbch = ReadISAC(isac, ISAC_RBCH);
		star = ReadISAC(isac, ISAC_STAR);
		pr_debug("%s: D-Channel Busy RBCH %02x STAR %02x\n",
			isac->name, rbch, star);
		if (rbch & ISAC_RBCH_XAC) /* D-Channel Busy */
			test_and_set_bit(FLG_L1_BUSY, &isac->dch.Flags);
		else {
			/* discard frame; reset transceiver */
			test_and_clear_bit(FLG_BUSY_TIMER, &isac->dch.Flags);
			if (isac->dch.tx_idx)
				isac->dch.tx_idx = 0;
			else
				pr_info("%s: ISAC D-Channel Busy no tx_idx\n",
					isac->name);
			/* Transmitter reset */
			WriteISAC(isac, ISAC_CMDR, 0x01);
		}
		spin_unlock_irqrestore(isac->hwlock, flags);
	}
}