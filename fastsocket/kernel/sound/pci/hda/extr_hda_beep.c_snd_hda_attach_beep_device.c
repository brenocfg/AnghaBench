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
struct hda_codec {scalar_t__ beep_mode; int addr; struct hda_beep* beep; TYPE_2__* bus; } ;
struct hda_beep {int nid; scalar_t__ mode; int /*<<< orphan*/  mutex; int /*<<< orphan*/  beep_work; int /*<<< orphan*/  unregister_work; int /*<<< orphan*/  register_work; struct hda_codec* codec; int /*<<< orphan*/  phys; } ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_DIGI_CONVERT_2 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HDA_BEEP_MODE_OFF ; 
 scalar_t__ HDA_BEEP_MODE_ON ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hda_beep*) ; 
 struct hda_beep* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_do_attach (struct hda_beep*) ; 
 int /*<<< orphan*/  snd_hda_do_register ; 
 int /*<<< orphan*/  snd_hda_do_unregister ; 
 int /*<<< orphan*/  snd_hda_generate_beep ; 
 int /*<<< orphan*/  snd_hda_get_bool_hint (struct hda_codec*,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 

int snd_hda_attach_beep_device(struct hda_codec *codec, int nid)
{
	struct hda_beep *beep;

	if (!snd_hda_get_bool_hint(codec, "beep"))
		return 0; /* disabled explicitly by hints */
	if (codec->beep_mode == HDA_BEEP_MODE_OFF)
		return 0; /* disabled by module option */

	beep = kzalloc(sizeof(*beep), GFP_KERNEL);
	if (beep == NULL)
		return -ENOMEM;
	snprintf(beep->phys, sizeof(beep->phys),
		"card%d/codec#%d/beep0", codec->bus->card->number, codec->addr);
	/* enable linear scale */
	snd_hda_codec_write_cache(codec, nid, 0,
		AC_VERB_SET_DIGI_CONVERT_2, 0x01);

	beep->nid = nid;
	beep->codec = codec;
	beep->mode = codec->beep_mode;
	codec->beep = beep;

	INIT_WORK(&beep->register_work, &snd_hda_do_register);
	INIT_DELAYED_WORK(&beep->unregister_work, &snd_hda_do_unregister);
	INIT_WORK(&beep->beep_work, &snd_hda_generate_beep);
	mutex_init(&beep->mutex);

	if (beep->mode == HDA_BEEP_MODE_ON) {
		int err = snd_hda_do_attach(beep);
		if (err < 0) {
			kfree(beep);
			codec->beep = NULL;
			return err;
		}
	}

	return 0;
}