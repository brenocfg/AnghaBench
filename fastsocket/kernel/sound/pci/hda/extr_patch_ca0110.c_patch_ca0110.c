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
struct hda_gen_spec {int multi_cap_vol; } ;
struct hda_codec {int /*<<< orphan*/  patch_ops; TYPE_1__* bus; struct hda_gen_spec* spec; } ;
struct TYPE_2__ {int needs_damn_long_delay; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ca0110_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  ca0110_patch_ops ; 
 struct hda_gen_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_free (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_gen_spec_init (struct hda_gen_spec*) ; 

__attribute__((used)) static int patch_ca0110(struct hda_codec *codec)
{
	struct hda_gen_spec *spec;
	int err;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;
	snd_hda_gen_spec_init(spec);
	codec->spec = spec;

	spec->multi_cap_vol = 1;
	codec->bus->needs_damn_long_delay = 1;

	err = ca0110_parse_auto_config(codec);
	if (err < 0)
		goto error;

	codec->patch_ops = ca0110_patch_ops;

	return 0;

 error:
	snd_hda_gen_free(codec);
	return err;
}