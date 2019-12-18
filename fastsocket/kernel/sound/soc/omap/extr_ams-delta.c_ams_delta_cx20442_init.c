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
struct snd_soc_dai {TYPE_3__* ops; } ;
struct snd_soc_codec {TYPE_1__* socdev; struct snd_soc_dai* dai; } ;
struct snd_soc_card {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {scalar_t__ digital_mute; } ;
struct TYPE_5__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  startup; } ;
struct TYPE_4__ {struct snd_soc_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  N_V253 ; 
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  ams_delta_audio_controls ; 
 int /*<<< orphan*/  ams_delta_audio_map ; 
 TYPE_3__ ams_delta_dai_ops ; 
 int /*<<< orphan*/  ams_delta_dapm_widgets ; 
 scalar_t__ ams_delta_digital_mute ; 
 int /*<<< orphan*/  ams_delta_hook_switch ; 
 int /*<<< orphan*/  ams_delta_hook_switch_gpios ; 
 TYPE_2__ ams_delta_ops ; 
 int /*<<< orphan*/  ams_delta_set_bias_level (struct snd_soc_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ams_delta_shutdown ; 
 int /*<<< orphan*/  ams_delta_startup ; 
 int /*<<< orphan*/  cx81801_ops ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int snd_soc_add_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 int snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_new (struct snd_soc_card*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tty_register_ldisc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ams_delta_cx20442_init(struct snd_soc_codec *codec)
{
	struct snd_soc_dai *codec_dai = codec->dai;
	struct snd_soc_card *card = codec->socdev->card;
	int ret;
	/* Codec is ready, now add/activate board specific controls */

	/* Set up digital mute if not provided by the codec */
	if (!codec_dai->ops) {
		codec_dai->ops = &ams_delta_dai_ops;
	} else if (!codec_dai->ops->digital_mute) {
		codec_dai->ops->digital_mute = ams_delta_digital_mute;
	} else {
		ams_delta_ops.startup = ams_delta_startup;
		ams_delta_ops.shutdown = ams_delta_shutdown;
	}

	/* Set codec bias level */
	ams_delta_set_bias_level(card, SND_SOC_BIAS_STANDBY);

	/* Add hook switch - can be used to control the codec from userspace
	 * even if line discipline fails */
	ret = snd_soc_jack_new(card, "hook_switch",
				SND_JACK_HEADSET, &ams_delta_hook_switch);
	if (ret)
		dev_warn(card->dev,
				"Failed to allocate resources for hook switch, "
				"will continue without one.\n");
	else {
		ret = snd_soc_jack_add_gpios(&ams_delta_hook_switch,
					ARRAY_SIZE(ams_delta_hook_switch_gpios),
					ams_delta_hook_switch_gpios);
		if (ret)
			dev_warn(card->dev,
				"Failed to set up hook switch GPIO line, "
				"will continue with hook switch inactive.\n");
	}

	/* Register optional line discipline for over the modem control */
	ret = tty_register_ldisc(N_V253, &cx81801_ops);
	if (ret) {
		dev_warn(card->dev,
				"Failed to register line discipline, "
				"will continue without any controls.\n");
		return 0;
	}

	/* Add board specific DAPM widgets and routes */
	ret = snd_soc_dapm_new_controls(codec, ams_delta_dapm_widgets,
					ARRAY_SIZE(ams_delta_dapm_widgets));
	if (ret) {
		dev_warn(card->dev,
				"Failed to register DAPM controls, "
				"will continue without any.\n");
		return 0;
	}

	ret = snd_soc_dapm_add_routes(codec, ams_delta_audio_map,
					ARRAY_SIZE(ams_delta_audio_map));
	if (ret) {
		dev_warn(card->dev,
				"Failed to set up DAPM routes, "
				"will continue with codec default map.\n");
		return 0;
	}

	/* Set up initial pin constellation */
	snd_soc_dapm_disable_pin(codec, "Mouthpiece");
	snd_soc_dapm_enable_pin(codec, "Earpiece");
	snd_soc_dapm_enable_pin(codec, "Microphone");
	snd_soc_dapm_disable_pin(codec, "Speaker");
	snd_soc_dapm_disable_pin(codec, "AGCIN");
	snd_soc_dapm_disable_pin(codec, "AGCOUT");
	snd_soc_dapm_sync(codec);

	/* Add virtual switch */
	ret = snd_soc_add_controls(codec, ams_delta_audio_controls,
					ARRAY_SIZE(ams_delta_audio_controls));
	if (ret)
		dev_warn(card->dev,
				"Failed to register audio mode control, "
				"will continue without it.\n");

	return 0;
}