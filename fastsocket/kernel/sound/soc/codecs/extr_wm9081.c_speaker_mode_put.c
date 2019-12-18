#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_codec {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WM9081_ANALOGUE_SPEAKER_2 ; 
 unsigned int WM9081_OUT_SPK_CTRL ; 
 int /*<<< orphan*/  WM9081_POWER_MANAGEMENT ; 
 unsigned int WM9081_SPK_ENA ; 
 unsigned int WM9081_SPK_INV_MUTE ; 
 unsigned int WM9081_SPK_MODE ; 
 struct snd_soc_codec* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int speaker_mode_put(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	unsigned int reg_pwr = snd_soc_read(codec, WM9081_POWER_MANAGEMENT);
	unsigned int reg2 = snd_soc_read(codec, WM9081_ANALOGUE_SPEAKER_2);

	/* Are we changing anything? */
	if (ucontrol->value.integer.value[0] ==
	    ((reg2 & WM9081_SPK_MODE) != 0))
		return 0;

	/* Don't try to change modes while enabled */
	if (reg_pwr & WM9081_SPK_ENA)
		return -EINVAL;

	if (ucontrol->value.integer.value[0]) {
		/* Class AB */
		reg2 &= ~(WM9081_SPK_INV_MUTE | WM9081_OUT_SPK_CTRL);
		reg2 |= WM9081_SPK_MODE;
	} else {
		/* Class D */
		reg2 |= WM9081_SPK_INV_MUTE | WM9081_OUT_SPK_CTRL;
		reg2 &= ~WM9081_SPK_MODE;
	}

	snd_soc_write(codec, WM9081_ANALOGUE_SPEAKER_2, reg2);

	return 0;
}