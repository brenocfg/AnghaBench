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
struct hfc_multi {int ledcount; int ledstate; int leds; size_t dslot; int /*<<< orphan*/  pci_iobase; TYPE_3__* chan; int /*<<< orphan*/  chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_5__ {TYPE_1__ D; } ;
struct dchannel {int state; TYPE_2__ dev; } ;
struct TYPE_6__ {int sync; struct dchannel* dch; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFC_CHIP_B410P ; 
 int /*<<< orphan*/  HFC_outb_nodebug (struct hfc_multi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISDN_P_NT_E1 ; 
 int /*<<< orphan*/  ISDN_P_NT_S0 ; 
 int /*<<< orphan*/  ISDN_P_TE_S0 ; 
 int /*<<< orphan*/  R_BRG_PCM_CFG ; 
 int /*<<< orphan*/  R_GPIO_EN1 ; 
 int /*<<< orphan*/  R_GPIO_OUT1 ; 
 int V_PCM_CLK ; 
 int /*<<< orphan*/  outl (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 scalar_t__ poll ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpm_out (struct hfc_multi*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
hfcmulti_leds(struct hfc_multi *hc)
{
	unsigned long lled;
	unsigned long leddw;
	int i, state, active, leds;
	struct dchannel *dch;
	int led[4];

	hc->ledcount += poll;
	if (hc->ledcount > 4096) {
		hc->ledcount -= 4096;
		hc->ledstate = 0xAFFEAFFE;
	}

	switch (hc->leds) {
	case 1: /* HFC-E1 OEM */
		/* 2 red blinking: NT mode deactivate
		 * 2 red steady:   TE mode deactivate
		 * left green:     L1 active
		 * left red:       frame sync, but no L1
		 * right green:    L2 active
		 */
		if (hc->chan[hc->dslot].sync != 2) { /* no frame sync */
			if (hc->chan[hc->dslot].dch->dev.D.protocol
				!= ISDN_P_NT_E1) {
				led[0] = 1;
				led[1] = 1;
			} else if (hc->ledcount>>11) {
				led[0] = 1;
				led[1] = 1;
			} else {
				led[0] = 0;
				led[1] = 0;
			}
			led[2] = 0;
			led[3] = 0;
		} else { /* with frame sync */
			/* TODO make it work */
			led[0] = 0;
			led[1] = 0;
			led[2] = 0;
			led[3] = 1;
		}
		leds = (led[0] | (led[1]<<2) | (led[2]<<1) | (led[3]<<3))^0xF;
			/* leds are inverted */
		if (leds != (int)hc->ledstate) {
			HFC_outb_nodebug(hc, R_GPIO_OUT1, leds);
			hc->ledstate = leds;
		}
		break;

	case 2: /* HFC-4S OEM */
		/* red blinking = PH_DEACTIVATE NT Mode
		 * red steady   = PH_DEACTIVATE TE Mode
		 * green steady = PH_ACTIVATE
		 */
		for (i = 0; i < 4; i++) {
			state = 0;
			active = -1;
			dch = hc->chan[(i << 2) | 2].dch;
			if (dch) {
				state = dch->state;
				if (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				else
					active = 7;
			}
			if (state) {
				if (state == active) {
					led[i] = 1; /* led green */
				} else
					if (dch->dev.D.protocol == ISDN_P_TE_S0)
						/* TE mode: led red */
						led[i] = 2;
					else
						if (hc->ledcount>>11)
							/* led red */
							led[i] = 2;
						else
							/* led off */
							led[i] = 0;
			} else
				led[i] = 0; /* led off */
		}
		if (test_bit(HFC_CHIP_B410P, &hc->chip)) {
			leds = 0;
			for (i = 0; i < 4; i++) {
				if (led[i] == 1) {
					/*green*/
					leds |= (0x2 << (i * 2));
				} else if (led[i] == 2) {
					/*red*/
					leds |= (0x1 << (i * 2));
				}
			}
			if (leds != (int)hc->ledstate) {
				vpm_out(hc, 0, 0x1a8 + 3, leds);
				hc->ledstate = leds;
			}
		} else {
			leds = ((led[3] > 0) << 0) | ((led[1] > 0) << 1) |
			    ((led[0] > 0) << 2) | ((led[2] > 0) << 3) |
			    ((led[3] & 1) << 4) | ((led[1] & 1) << 5) |
			    ((led[0] & 1) << 6) | ((led[2] & 1) << 7);
			if (leds != (int)hc->ledstate) {
				HFC_outb_nodebug(hc, R_GPIO_EN1, leds & 0x0F);
				HFC_outb_nodebug(hc, R_GPIO_OUT1, leds >> 4);
				hc->ledstate = leds;
			}
		}
		break;

	case 3: /* HFC 1S/2S Beronet */
		/* red blinking = PH_DEACTIVATE NT Mode
		 * red steady   = PH_DEACTIVATE TE Mode
		 * green steady = PH_ACTIVATE
		 */
		for (i = 0; i < 2; i++) {
			state = 0;
			active = -1;
			dch = hc->chan[(i << 2) | 2].dch;
			if (dch) {
				state = dch->state;
				if (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				else
					active = 7;
			}
			if (state) {
				if (state == active) {
					led[i] = 1; /* led green */
				} else
					if (dch->dev.D.protocol == ISDN_P_TE_S0)
						/* TE mode: led red */
						led[i] = 2;
					else
						if (hc->ledcount >> 11)
							/* led red */
							led[i] = 2;
						else
							/* led off */
							led[i] = 0;
			} else
				led[i] = 0; /* led off */
		}


		leds = (led[0] > 0) | ((led[1] > 0)<<1) | ((led[0]&1)<<2)
			| ((led[1]&1)<<3);
		if (leds != (int)hc->ledstate) {
			HFC_outb_nodebug(hc, R_GPIO_EN1,
			    ((led[0] > 0) << 2) | ((led[1] > 0) << 3));
			HFC_outb_nodebug(hc, R_GPIO_OUT1,
			    ((led[0] & 1) << 2) | ((led[1] & 1) << 3));
			hc->ledstate = leds;
		}
		break;
	case 8: /* HFC 8S+ Beronet */
		lled = 0;

		for (i = 0; i < 8; i++) {
			state = 0;
			active = -1;
			dch = hc->chan[(i << 2) | 2].dch;
			if (dch) {
				state = dch->state;
				if (dch->dev.D.protocol == ISDN_P_NT_S0)
					active = 3;
				else
					active = 7;
			}
			if (state) {
				if (state == active) {
					lled |= 0 << i;
				} else
					if (hc->ledcount >> 11)
						lled |= 0 << i;
					else
						lled |= 1 << i;
			} else
				lled |= 1 << i;
		}
		leddw = lled << 24 | lled << 16 | lled << 8 | lled;
		if (leddw != hc->ledstate) {
			/* HFC_outb(hc, R_BRG_PCM_CFG, 1);
			HFC_outb(c, R_BRG_PCM_CFG, (0x0 << 6) | 0x3); */
			/* was _io before */
			HFC_outb_nodebug(hc, R_BRG_PCM_CFG, 1 | V_PCM_CLK);
			outw(0x4000, hc->pci_iobase + 4);
			outl(leddw, hc->pci_iobase);
			HFC_outb_nodebug(hc, R_BRG_PCM_CFG, V_PCM_CLK);
			hc->ledstate = leddw;
		}
		break;
	}
}