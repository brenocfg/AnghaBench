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
struct hda_codec {int dummy; } ;
struct auto_pin_cfg {int num_inputs; TYPE_1__* inputs; } ;
struct TYPE_2__ {int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int INPUT_PIN_ATTR_NORMAL ; 
 unsigned int snd_hda_codec_get_pincfg (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_get_input_pin_attr (unsigned int) ; 

__attribute__((used)) static int check_mic_location_need(struct hda_codec *codec,
				   const struct auto_pin_cfg *cfg,
				   int input)
{
	unsigned int defc;
	int i, attr, attr2;

	defc = snd_hda_codec_get_pincfg(codec, cfg->inputs[input].pin);
	attr = snd_hda_get_input_pin_attr(defc);
	/* for internal or docking mics, we need locations */
	if (attr <= INPUT_PIN_ATTR_NORMAL)
		return 1;

	attr = 0;
	for (i = 0; i < cfg->num_inputs; i++) {
		defc = snd_hda_codec_get_pincfg(codec, cfg->inputs[i].pin);
		attr2 = snd_hda_get_input_pin_attr(defc);
		if (attr2 >= INPUT_PIN_ATTR_NORMAL) {
			if (attr && attr != attr2)
				return 1; /* different locations found */
			attr = attr2;
		}
	}
	return 0;
}