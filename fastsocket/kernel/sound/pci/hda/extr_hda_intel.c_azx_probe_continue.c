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
struct azx {int dev_index; int running; int init_failed; int /*<<< orphan*/  card; int /*<<< orphan*/  bus; TYPE_1__* fw; int /*<<< orphan*/  beep_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  azx_add_card_list (struct azx*) ; 
 int azx_codec_configure (struct azx*) ; 
 int azx_codec_create (struct azx*,int /*<<< orphan*/ ) ; 
 int azx_mixer_create (struct azx*) ; 
 int /*<<< orphan*/  azx_notifier_register (struct azx*) ; 
 int /*<<< orphan*/ * beep_mode ; 
 int /*<<< orphan*/ * model ; 
 int /*<<< orphan*/  power_down_all_codecs (struct azx*) ; 
 int* probe_only ; 
 int /*<<< orphan*/  release_firmware (TYPE_1__*) ; 
 int snd_card_register (int /*<<< orphan*/ ) ; 
 int snd_hda_build_pcms (int /*<<< orphan*/ ) ; 
 int snd_hda_load_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int azx_probe_continue(struct azx *chip)
{
	int dev = chip->dev_index;
	int err;

#ifdef CONFIG_SND_HDA_INPUT_BEEP
	chip->beep_mode = beep_mode[dev];
#endif

	/* create codec instances */
	err = azx_codec_create(chip, model[dev]);
	if (err < 0)
		goto out_free;
#ifdef CONFIG_SND_HDA_PATCH_LOADER
	if (chip->fw) {
		err = snd_hda_load_patch(chip->bus, chip->fw->size,
					 chip->fw->data);
		if (err < 0)
			goto out_free;
#ifndef CONFIG_PM
		release_firmware(chip->fw); /* no longer needed */
		chip->fw = NULL;
#endif
	}
#endif
	if ((probe_only[dev] & 1) == 0) {
		err = azx_codec_configure(chip);
		if (err < 0)
			goto out_free;
	}

	/* create PCM streams */
	err = snd_hda_build_pcms(chip->bus);
	if (err < 0)
		goto out_free;

	/* create mixer controls */
	err = azx_mixer_create(chip);
	if (err < 0)
		goto out_free;

	err = snd_card_register(chip->card);
	if (err < 0)
		goto out_free;

	chip->running = 1;
	power_down_all_codecs(chip);
	azx_notifier_register(chip);
	azx_add_card_list(chip);

	return 0;

out_free:
	chip->init_failed = 1;
	return err;
}