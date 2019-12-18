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
typedef  int u16 ;
struct wm97xx {int pen_probably_down; int /*<<< orphan*/  dev; TYPE_1__* mach_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* post_sample ) (int) ;int /*<<< orphan*/  (* pre_sample ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_LINK_FRAME ; 
 int /*<<< orphan*/  AC97_WM9713_DIG1 ; 
 int /*<<< orphan*/  AC97_WM97XX_DIGITISER_RD ; 
 int RC_PENUP ; 
 int RC_VALID ; 
 int WM9713_ADCSEL_MASK ; 
 int WM9713_POLL ; 
 int WM97XX_ADCSRC_MASK ; 
 int WM97XX_PEN_DOWN ; 
 int delay ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int ffs (int) ; 
 scalar_t__ is_pden (struct wm97xx*) ; 
 int /*<<< orphan*/  poll_delay (int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int wm97xx_reg_read (struct wm97xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm97xx_reg_write (struct wm97xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm9713_poll_sample(struct wm97xx *wm, int adcsel, int *sample)
{
	u16 dig1;
	int timeout = 5 * delay;

	if (!wm->pen_probably_down) {
		u16 data = wm97xx_reg_read(wm, AC97_WM97XX_DIGITISER_RD);
		if (!(data & WM97XX_PEN_DOWN))
			return RC_PENUP;
		wm->pen_probably_down = 1;
	}

	/* set up digitiser */
	if (adcsel & 0x8000)
		adcsel = 1 << ((adcsel & 0x7fff) + 3);

	dig1 = wm97xx_reg_read(wm, AC97_WM9713_DIG1);
	dig1 &= ~WM9713_ADCSEL_MASK;

	if (wm->mach_ops && wm->mach_ops->pre_sample)
		wm->mach_ops->pre_sample(adcsel);
	wm97xx_reg_write(wm, AC97_WM9713_DIG1, dig1 | adcsel | WM9713_POLL);

	/* wait 3 AC97 time slots + delay for conversion */
	poll_delay(delay);

	/* wait for POLL to go low */
	while ((wm97xx_reg_read(wm, AC97_WM9713_DIG1) & WM9713_POLL) &&
		timeout) {
		udelay(AC97_LINK_FRAME);
		timeout--;
	}

	if (timeout <= 0) {
		/* If PDEN is set, we can get a timeout when pen goes up */
		if (is_pden(wm))
			wm->pen_probably_down = 0;
		else
			dev_dbg(wm->dev, "adc sample timeout");
		return RC_PENUP;
	}

	*sample = wm97xx_reg_read(wm, AC97_WM97XX_DIGITISER_RD);
	if (wm->mach_ops && wm->mach_ops->post_sample)
		wm->mach_ops->post_sample(adcsel);

	/* check we have correct sample */
	if ((*sample & WM97XX_ADCSRC_MASK) != ffs(adcsel >> 1) << 12) {
		dev_dbg(wm->dev, "adc wrong sample, read %x got %x", adcsel,
			*sample & WM97XX_ADCSRC_MASK);
		return RC_PENUP;
	}

	if (!(*sample & WM97XX_PEN_DOWN)) {
		wm->pen_probably_down = 0;
		return RC_PENUP;
	}

	return RC_VALID;
}