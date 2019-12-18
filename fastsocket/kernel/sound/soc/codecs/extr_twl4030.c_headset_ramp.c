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
struct twl4030_setup_data {int /*<<< orphan*/  (* set_hs_extmute ) (int) ;scalar_t__ hs_extmute; } ;
struct twl4030_priv {unsigned int sysclk; } ;
struct snd_soc_device {struct twl4030_setup_data* codec_data; } ;
struct snd_soc_codec {struct twl4030_priv* private_data; struct snd_soc_device* socdev; } ;

/* Variables and functions */
 unsigned char TWL4030_EXTMUTE ; 
 int /*<<< orphan*/  TWL4030_MODULE_AUDIO_VOICE ; 
 unsigned char TWL4030_RAMP_DELAY ; 
 unsigned char TWL4030_RAMP_EN ; 
 int /*<<< orphan*/  TWL4030_REG_HS_GAIN_SET ; 
 int /*<<< orphan*/  TWL4030_REG_HS_POPN_SET ; 
 unsigned char TWL4030_VMID_EN ; 
 int /*<<< orphan*/  mdelay (unsigned int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  twl4030_i2c_write_u8 (int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ) ; 
 unsigned char twl4030_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_write (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void headset_ramp(struct snd_soc_codec *codec, int ramp)
{
	struct snd_soc_device *socdev = codec->socdev;
	struct twl4030_setup_data *setup = socdev->codec_data;

	unsigned char hs_gain, hs_pop;
	struct twl4030_priv *twl4030 = codec->private_data;
	/* Base values for ramp delay calculation: 2^19 - 2^26 */
	unsigned int ramp_base[] = {524288, 1048576, 2097152, 4194304,
				    8388608, 16777216, 33554432, 67108864};

	hs_gain = twl4030_read_reg_cache(codec, TWL4030_REG_HS_GAIN_SET);
	hs_pop = twl4030_read_reg_cache(codec, TWL4030_REG_HS_POPN_SET);

	/* Enable external mute control, this dramatically reduces
	 * the pop-noise */
	if (setup && setup->hs_extmute) {
		if (setup->set_hs_extmute) {
			setup->set_hs_extmute(1);
		} else {
			hs_pop |= TWL4030_EXTMUTE;
			twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);
		}
	}

	if (ramp) {
		/* Headset ramp-up according to the TRM */
		hs_pop |= TWL4030_VMID_EN;
		twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);
		twl4030_write(codec, TWL4030_REG_HS_GAIN_SET, hs_gain);
		hs_pop |= TWL4030_RAMP_EN;
		twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);
		/* Wait ramp delay time + 1, so the VMID can settle */
		mdelay((ramp_base[(hs_pop & TWL4030_RAMP_DELAY) >> 2] /
			twl4030->sysclk) + 1);
	} else {
		/* Headset ramp-down _not_ according to
		 * the TRM, but in a way that it is working */
		hs_pop &= ~TWL4030_RAMP_EN;
		twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);
		/* Wait ramp delay time + 1, so the VMID can settle */
		mdelay((ramp_base[(hs_pop & TWL4030_RAMP_DELAY) >> 2] /
			twl4030->sysclk) + 1);
		/* Bypass the reg_cache to mute the headset */
		twl4030_i2c_write_u8(TWL4030_MODULE_AUDIO_VOICE,
					hs_gain & (~0x0f),
					TWL4030_REG_HS_GAIN_SET);

		hs_pop &= ~TWL4030_VMID_EN;
		twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);
	}

	/* Disable external mute */
	if (setup && setup->hs_extmute) {
		if (setup->set_hs_extmute) {
			setup->set_hs_extmute(0);
		} else {
			hs_pop &= ~TWL4030_EXTMUTE;
			twl4030_write(codec, TWL4030_REG_HS_POPN_SET, hs_pop);
		}
	}
}