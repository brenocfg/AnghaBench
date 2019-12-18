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
struct hda_codec {struct cs_spec* spec; } ;
struct cs_spec {scalar_t__ gpio_data; scalar_t__ gpio_dir; scalar_t__ gpio_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DATA ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DIRECTION ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_MASK ; 
 int /*<<< orphan*/  cs_coef_init_verbs ; 
 int /*<<< orphan*/  cs_errata_init_verbs ; 
 int /*<<< orphan*/  init_digital_coef (struct hda_codec*) ; 
 int /*<<< orphan*/  init_input_coef (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  snd_hda_gen_init (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_sequence_write (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs_init(struct hda_codec *codec)
{
	struct cs_spec *spec = codec->spec;

	/* init_verb sequence for C0/C1/C2 errata*/
	snd_hda_sequence_write(codec, cs_errata_init_verbs);

	snd_hda_sequence_write(codec, cs_coef_init_verbs);

	snd_hda_gen_init(codec);

	if (spec->gpio_mask) {
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_MASK,
				    spec->gpio_mask);
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_DIRECTION,
				    spec->gpio_dir);
		snd_hda_codec_write(codec, 0x01, 0, AC_VERB_SET_GPIO_DATA,
				    spec->gpio_data);
	}

	init_input_coef(codec);
	init_digital_coef(codec);

	return 0;
}