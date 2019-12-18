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
typedef  int /*<<< orphan*/  u32 ;
struct w6692_hw {int fmask; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  Flags; int /*<<< orphan*/  nr; struct w6692_hw* hw; } ;
struct w6692_ch {int b_mode; TYPE_1__ bch; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  FLG_HDLC ; 
 int /*<<< orphan*/  FLG_TRANSPARENT ; 
#define  ISDN_P_B_HDLC 130 
#define  ISDN_P_B_RAW 129 
#define  ISDN_P_NONE 128 
 int /*<<< orphan*/  W_B_ADM1 ; 
 int /*<<< orphan*/  W_B_ADM2 ; 
 int /*<<< orphan*/  W_B_CMDR ; 
 int W_B_CMDR_RACT ; 
 int W_B_CMDR_RRST ; 
 int W_B_CMDR_XRST ; 
 int /*<<< orphan*/  W_B_EXIM ; 
 int /*<<< orphan*/  W_B_MODE ; 
 int W_B_MODE_EPCM ; 
 int W_B_MODE_ITF ; 
 int W_B_MODE_MMS ; 
 int /*<<< orphan*/  WriteW6692B (struct w6692_ch*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  disable_pots (struct w6692_ch*) ; 
 int /*<<< orphan*/  mISDN_clear_bchannel (TYPE_1__*) ; 
 int pots ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
w6692_mode(struct w6692_ch *wch, u32 pr)
{
	struct w6692_hw	*card;

	card = wch->bch.hw;
	pr_debug("%s: B%d protocol %x-->%x\n", card->name,
		wch->bch.nr, wch->bch.state, pr);
	switch (pr) {
	case ISDN_P_NONE:
		if ((card->fmask & pots) && (wch->b_mode & W_B_MODE_EPCM))
			disable_pots(wch);
		wch->b_mode = 0;
		mISDN_clear_bchannel(&wch->bch);
		WriteW6692B(wch, W_B_MODE, wch->b_mode);
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_XRST);
		test_and_clear_bit(FLG_HDLC, &wch->bch.Flags);
		test_and_clear_bit(FLG_TRANSPARENT, &wch->bch.Flags);
		break;
	case ISDN_P_B_RAW:
		wch->b_mode = W_B_MODE_MMS;
		WriteW6692B(wch, W_B_MODE, wch->b_mode);
		WriteW6692B(wch, W_B_EXIM, 0);
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_RACT |
			W_B_CMDR_XRST);
		test_and_set_bit(FLG_TRANSPARENT, &wch->bch.Flags);
		break;
	case ISDN_P_B_HDLC:
		wch->b_mode = W_B_MODE_ITF;
		WriteW6692B(wch, W_B_MODE, wch->b_mode);
		WriteW6692B(wch, W_B_ADM1, 0xff);
		WriteW6692B(wch, W_B_ADM2, 0xff);
		WriteW6692B(wch, W_B_EXIM, 0);
		WriteW6692B(wch, W_B_CMDR, W_B_CMDR_RRST | W_B_CMDR_RACT |
			W_B_CMDR_XRST);
		test_and_set_bit(FLG_HDLC, &wch->bch.Flags);
		break;
	default:
		pr_info("%s: protocol %x not known\n", card->name, pr);
		return -ENOPROTOOPT;
	}
	wch->bch.state = pr;
	return 0;
}