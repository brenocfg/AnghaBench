#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long recsrc; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_HAVEDIGITAL ; 
 int /*<<< orphan*/  HDEXAR_SET_ANA_IN ; 
 int /*<<< orphan*/  HDEXAR_SET_DAT_IN ; 
 int /*<<< orphan*/  HDEXAR_SET_SYNTH_IN ; 
 int /*<<< orphan*/  HDEX_AUX_REQ ; 
 int SOUND_MASK_DIGITAL1 ; 
 int SOUND_MASK_IMIX ; 
 int SOUND_MASK_SYNTH ; 
 int /*<<< orphan*/  chk_send_dsp_cmd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ dev ; 
 scalar_t__ msnd_send_word (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long set_recsrc(unsigned long recsrc)
{
	if (dev.recsrc == recsrc)
		return dev.recsrc;
#ifdef HAVE_NORECSRC
	else if (recsrc == 0)
		dev.recsrc = 0;
#endif
	else
		dev.recsrc ^= recsrc;

#ifndef MSND_CLASSIC
	if (dev.recsrc & SOUND_MASK_IMIX) {
		if (msnd_send_word(&dev, 0, 0, HDEXAR_SET_ANA_IN) == 0)
			chk_send_dsp_cmd(&dev, HDEX_AUX_REQ);
	}
	else if (dev.recsrc & SOUND_MASK_SYNTH) {
		if (msnd_send_word(&dev, 0, 0, HDEXAR_SET_SYNTH_IN) == 0)
			chk_send_dsp_cmd(&dev, HDEX_AUX_REQ);
	}
	else if ((dev.recsrc & SOUND_MASK_DIGITAL1) && test_bit(F_HAVEDIGITAL, &dev.flags)) {
		if (msnd_send_word(&dev, 0, 0, HDEXAR_SET_DAT_IN) == 0)
      			chk_send_dsp_cmd(&dev, HDEX_AUX_REQ);
	}
	else {
#ifdef HAVE_NORECSRC
		/* Select no input (?) */
		dev.recsrc = 0;
#else
		dev.recsrc = SOUND_MASK_IMIX;
		if (msnd_send_word(&dev, 0, 0, HDEXAR_SET_ANA_IN) == 0)
			chk_send_dsp_cmd(&dev, HDEX_AUX_REQ);
#endif
	}
#endif /* MSND_CLASSIC */

	return dev.recsrc;
}