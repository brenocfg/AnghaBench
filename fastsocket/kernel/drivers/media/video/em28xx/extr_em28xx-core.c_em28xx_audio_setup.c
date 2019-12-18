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
typedef  int u32 ;
struct TYPE_2__ {int has_audio; int i2s_3rates; int i2s_5rates; int ac97; int ac97_vendor_id; int ac97_feat; } ;
struct em28xx {scalar_t__ chip_id; int has_alsa_audio; TYPE_1__ audio_mode; scalar_t__ has_audio_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_RESET ; 
 int /*<<< orphan*/  AC97_VENDOR_ID1 ; 
 int /*<<< orphan*/  AC97_VENDOR_ID2 ; 
 scalar_t__ CHIP_ID_EM2870 ; 
 scalar_t__ CHIP_ID_EM2874 ; 
#define  EM28XX_AC97_EM202 131 
#define  EM28XX_AC97_OTHER 130 
#define  EM28XX_AC97_SIGMATEL 129 
 int EM28XX_CHIPCFG_AC97 ; 
 int EM28XX_CHIPCFG_AUDIOMASK ; 
 int EM28XX_CHIPCFG_I2S_3_SAMPRATES ; 
 int EM28XX_CHIPCFG_I2S_5_SAMPRATES ; 
#define  EM28XX_NO_AC97 128 
 int /*<<< orphan*/  EM28XX_R00_CHIPCFG ; 
 int em28xx_audio_analog_set (struct em28xx*) ; 
 int /*<<< orphan*/  em28xx_info (char*,...) ; 
 int em28xx_read_ac97 (struct em28xx*,int /*<<< orphan*/ ) ; 
 int em28xx_read_reg (struct em28xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em28xx_warn (char*,...) ; 

int em28xx_audio_setup(struct em28xx *dev)
{
	int vid1, vid2, feat, cfg;
	u32 vid;

	if (dev->chip_id == CHIP_ID_EM2870 || dev->chip_id == CHIP_ID_EM2874) {
		/* Digital only device - don't load any alsa module */
		dev->audio_mode.has_audio = 0;
		dev->has_audio_class = 0;
		dev->has_alsa_audio = 0;
		return 0;
	}

	/* If device doesn't support Usb Audio Class, use vendor class */
	if (!dev->has_audio_class)
		dev->has_alsa_audio = 1;

	dev->audio_mode.has_audio = 1;

	/* See how this device is configured */
	cfg = em28xx_read_reg(dev, EM28XX_R00_CHIPCFG);
	em28xx_info("Config register raw data: 0x%02x\n", cfg);
	if (cfg < 0) {
		/* Register read error?  */
		cfg = EM28XX_CHIPCFG_AC97; /* Be conservative */
	} else if ((cfg & EM28XX_CHIPCFG_AUDIOMASK) == 0x00) {
		/* The device doesn't have vendor audio at all */
		dev->has_alsa_audio = 0;
		dev->audio_mode.has_audio = 0;
		return 0;
	} else if ((cfg & EM28XX_CHIPCFG_AUDIOMASK) ==
		   EM28XX_CHIPCFG_I2S_3_SAMPRATES) {
		em28xx_info("I2S Audio (3 sample rates)\n");
		dev->audio_mode.i2s_3rates = 1;
	} else if ((cfg & EM28XX_CHIPCFG_AUDIOMASK) ==
		   EM28XX_CHIPCFG_I2S_5_SAMPRATES) {
		em28xx_info("I2S Audio (5 sample rates)\n");
		dev->audio_mode.i2s_5rates = 1;
	}

	if ((cfg & EM28XX_CHIPCFG_AUDIOMASK) != EM28XX_CHIPCFG_AC97) {
		/* Skip the code that does AC97 vendor detection */
		dev->audio_mode.ac97 = EM28XX_NO_AC97;
		goto init_audio;
	}

	dev->audio_mode.ac97 = EM28XX_AC97_OTHER;

	vid1 = em28xx_read_ac97(dev, AC97_VENDOR_ID1);
	if (vid1 < 0) {
		/*
		 * Device likely doesn't support AC97
		 * Note: (some) em2800 devices without eeprom reports 0x91 on
		 *	 CHIPCFG register, even not having an AC97 chip
		 */
		em28xx_warn("AC97 chip type couldn't be determined\n");
		dev->audio_mode.ac97 = EM28XX_NO_AC97;
		dev->has_alsa_audio = 0;
		dev->audio_mode.has_audio = 0;
		goto init_audio;
	}

	vid2 = em28xx_read_ac97(dev, AC97_VENDOR_ID2);
	if (vid2 < 0)
		goto init_audio;

	vid = vid1 << 16 | vid2;

	dev->audio_mode.ac97_vendor_id = vid;
	em28xx_warn("AC97 vendor ID = 0x%08x\n", vid);

	feat = em28xx_read_ac97(dev, AC97_RESET);
	if (feat < 0)
		goto init_audio;

	dev->audio_mode.ac97_feat = feat;
	em28xx_warn("AC97 features = 0x%04x\n", feat);

	/* Try to identify what audio processor we have */
	if ((vid == 0xffffffff) && (feat == 0x6a90))
		dev->audio_mode.ac97 = EM28XX_AC97_EM202;
	else if ((vid >> 8) == 0x838476)
		dev->audio_mode.ac97 = EM28XX_AC97_SIGMATEL;

init_audio:
	/* Reports detected AC97 processor */
	switch (dev->audio_mode.ac97) {
	case EM28XX_NO_AC97:
		em28xx_info("No AC97 audio processor\n");
		break;
	case EM28XX_AC97_EM202:
		em28xx_info("Empia 202 AC97 audio processor detected\n");
		break;
	case EM28XX_AC97_SIGMATEL:
		em28xx_info("Sigmatel audio processor detected(stac 97%02x)\n",
			    dev->audio_mode.ac97_vendor_id & 0xff);
		break;
	case EM28XX_AC97_OTHER:
		em28xx_warn("Unknown AC97 audio processor detected!\n");
		break;
	default:
		break;
	}

	return em28xx_audio_analog_set(dev);
}