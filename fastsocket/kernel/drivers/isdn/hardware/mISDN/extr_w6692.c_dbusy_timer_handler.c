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
typedef  int /*<<< orphan*/  u_long ;
struct w6692_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; } ;
struct dchannel {scalar_t__ tx_idx; int /*<<< orphan*/  Flags; struct w6692_hw* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_BUSY_TIMER ; 
 int /*<<< orphan*/  FLG_L1_BUSY ; 
 int ReadW6692 (struct w6692_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W_D_CMDR ; 
 int /*<<< orphan*/  W_D_CMDR_XRST ; 
 int /*<<< orphan*/  W_D_RBCH ; 
 int /*<<< orphan*/  W_D_STAR ; 
 int W_D_STAR_XBZ ; 
 int /*<<< orphan*/  WriteW6692 (struct w6692_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dbusy_timer_handler(struct dchannel *dch)
{
	struct w6692_hw	*card = dch->hw;
	int		rbch, star;
	u_long		flags;

	if (test_bit(FLG_BUSY_TIMER, &dch->Flags)) {
		spin_lock_irqsave(&card->lock, flags);
		rbch = ReadW6692(card, W_D_RBCH);
		star = ReadW6692(card, W_D_STAR);
		pr_debug("%s: D-Channel Busy RBCH %02x STAR %02x\n",
			card->name, rbch, star);
		if (star & W_D_STAR_XBZ)	/* D-Channel Busy */
			test_and_set_bit(FLG_L1_BUSY, &dch->Flags);
		else {
			/* discard frame; reset transceiver */
			test_and_clear_bit(FLG_BUSY_TIMER, &dch->Flags);
			if (dch->tx_idx)
				dch->tx_idx = 0;
			else
				pr_info("%s: W6692 D-Channel Busy no tx_idx\n",
					card->name);
			/* Transmitter reset */
			WriteW6692(card, W_D_CMDR, W_D_CMDR_XRST);
		}
		spin_unlock_irqrestore(&card->lock, flags);
	}
}