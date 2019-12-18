#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* setup_rate ) (struct snd_ice1712*,unsigned int) ;} ;
struct TYPE_9__ {TYPE_3__ ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_pro_rate ) (struct snd_ice1712*,unsigned int) ;} ;
struct snd_ice1712 {unsigned int akm_codecs; TYPE_4__ spdif; TYPE_5__* akm; TYPE_1__ gpio; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_rate_val ) (TYPE_5__*,unsigned int) ;} ;
struct TYPE_10__ {TYPE_2__ ops; } ;

/* Variables and functions */
 int ICE1712_CAPTURE_START_SHADOW ; 
 int ICE1712_PLAYBACK_PAUSE ; 
 int ICE1712_PLAYBACK_START ; 
 int /*<<< orphan*/  ICEMT (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLAYBACK_CONTROL ; 
 int /*<<< orphan*/  RATE ; 
 int inb (int /*<<< orphan*/ ) ; 
 scalar_t__ is_pro_rate_locked (struct snd_ice1712*) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static void snd_ice1712_set_pro_rate(struct snd_ice1712 *ice, unsigned int rate, int force)
{
	unsigned long flags;
	unsigned char val, old;
	unsigned int i;

	switch (rate) {
	case 8000: val = 6; break;
	case 9600: val = 3; break;
	case 11025: val = 10; break;
	case 12000: val = 2; break;
	case 16000: val = 5; break;
	case 22050: val = 9; break;
	case 24000: val = 1; break;
	case 32000: val = 4; break;
	case 44100: val = 8; break;
	case 48000: val = 0; break;
	case 64000: val = 15; break;
	case 88200: val = 11; break;
	case 96000: val = 7; break;
	default:
		snd_BUG();
		val = 0;
		rate = 48000;
		break;
	}

	spin_lock_irqsave(&ice->reg_lock, flags);
	if (inb(ICEMT(ice, PLAYBACK_CONTROL)) & (ICE1712_CAPTURE_START_SHADOW|
						 ICE1712_PLAYBACK_PAUSE|
						 ICE1712_PLAYBACK_START)) {
__out:
		spin_unlock_irqrestore(&ice->reg_lock, flags);
		return;
	}
	if (!force && is_pro_rate_locked(ice))
		goto __out;

	old = inb(ICEMT(ice, RATE));
	if (!force && old == val)
		goto __out;
	outb(val, ICEMT(ice, RATE));
	spin_unlock_irqrestore(&ice->reg_lock, flags);

	if (ice->gpio.set_pro_rate)
		ice->gpio.set_pro_rate(ice, rate);
	for (i = 0; i < ice->akm_codecs; i++) {
		if (ice->akm[i].ops.set_rate_val)
			ice->akm[i].ops.set_rate_val(&ice->akm[i], rate);
	}
	if (ice->spdif.ops.setup_rate)
		ice->spdif.ops.setup_rate(ice, rate);
}