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
struct hda_pincfg {void* ctrl; void* cfg; scalar_t__ nid; } ;
struct hda_codec {int num_nodes; int /*<<< orphan*/  init_pins; scalar_t__ start_nid; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_CONFIG_DEFAULT ; 
 int /*<<< orphan*/  AC_VERB_GET_PIN_WIDGET_CONTROL ; 
 unsigned int AC_WID_PIN ; 
 int ENOMEM ; 
 unsigned int get_wcaps (struct hda_codec*,scalar_t__) ; 
 unsigned int get_wcaps_type (unsigned int) ; 
 struct hda_pincfg* snd_array_new (int /*<<< orphan*/ *) ; 
 void* snd_hda_codec_read (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_pin_defaults(struct hda_codec *codec)
{
	int i;
	hda_nid_t nid = codec->start_nid;

	for (i = 0; i < codec->num_nodes; i++, nid++) {
		struct hda_pincfg *pin;
		unsigned int wcaps = get_wcaps(codec, nid);
		unsigned int wid_type = get_wcaps_type(wcaps);
		if (wid_type != AC_WID_PIN)
			continue;
		pin = snd_array_new(&codec->init_pins);
		if (!pin)
			return -ENOMEM;
		pin->nid = nid;
		pin->cfg = snd_hda_codec_read(codec, nid, 0,
					      AC_VERB_GET_CONFIG_DEFAULT, 0);
		pin->ctrl = snd_hda_codec_read(codec, nid, 0,
					       AC_VERB_GET_PIN_WIDGET_CONTROL,
					       0);
	}
	return 0;
}