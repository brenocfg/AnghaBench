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
struct TYPE_4__ {int mixer_nid; } ;
struct via_spec {int /*<<< orphan*/  set_widgets_power_state; int /*<<< orphan*/  num_iverbs; int /*<<< orphan*/ * init_verbs; TYPE_1__ gen; } ;
struct hda_codec {char* chip_name; char* vendor_name; int vendor_id; int /*<<< orphan*/  patch_ops; TYPE_3__* bus; } ;
struct TYPE_6__ {TYPE_2__* card; } ;
struct TYPE_5__ {int /*<<< orphan*/  mixername; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ VT1708BCE ; 
 scalar_t__ get_codec_type (struct hda_codec*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  override_mic_boost (struct hda_codec*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_widgets_power_state_vt1708B ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  via_free (struct hda_codec*) ; 
 struct via_spec* via_new_spec (struct hda_codec*) ; 
 int via_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  via_patch_ops ; 
 int /*<<< orphan*/  vt1708S_init_verbs ; 

__attribute__((used)) static int patch_vt1708S(struct hda_codec *codec)
{
	struct via_spec *spec;
	int err;

	/* create a codec specific record */
	spec = via_new_spec(codec);
	if (spec == NULL)
		return -ENOMEM;

	spec->gen.mixer_nid = 0x16;
	override_mic_boost(codec, 0x1a, 0, 3, 40);
	override_mic_boost(codec, 0x1e, 0, 3, 40);

	/* correct names for VT1708BCE */
	if (get_codec_type(codec) == VT1708BCE)	{
		kfree(codec->chip_name);
		codec->chip_name = kstrdup("VT1708BCE", GFP_KERNEL);
		snprintf(codec->bus->card->mixername,
			 sizeof(codec->bus->card->mixername),
			 "%s %s", codec->vendor_name, codec->chip_name);
	}
	/* correct names for VT1705 */
	if (codec->vendor_id == 0x11064397)	{
		kfree(codec->chip_name);
		codec->chip_name = kstrdup("VT1705", GFP_KERNEL);
		snprintf(codec->bus->card->mixername,
			 sizeof(codec->bus->card->mixername),
			 "%s %s", codec->vendor_name, codec->chip_name);
	}

	/* automatic parse from the BIOS config */
	err = via_parse_auto_config(codec);
	if (err < 0) {
		via_free(codec);
		return err;
	}

	spec->init_verbs[spec->num_iverbs++] = vt1708S_init_verbs;

	codec->patch_ops = via_patch_ops;

	spec->set_widgets_power_state =  set_widgets_power_state_vt1708B;
	return 0;
}