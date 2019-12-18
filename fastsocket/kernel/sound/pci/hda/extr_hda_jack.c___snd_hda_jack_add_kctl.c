#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct hda_jack_tbl {int phantom_jack; int /*<<< orphan*/  type; TYPE_2__* jack; struct snd_kcontrol* kctl; } ;
struct hda_codec {TYPE_1__* bus; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_5__ {int /*<<< orphan*/  private_free; struct hda_jack_tbl* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  get_input_jack_type (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_free_jack_priv ; 
 int snd_hda_ctl_add (struct hda_codec*,int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 int snd_hda_jack_detect (struct hda_codec*,int /*<<< orphan*/ ) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_new (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_jack_new (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  snd_jack_report (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_kctl_jack_new (char const*,int,struct hda_codec*) ; 
 int /*<<< orphan*/  snd_kctl_jack_report (int /*<<< orphan*/ ,struct snd_kcontrol*,int) ; 

__attribute__((used)) static int __snd_hda_jack_add_kctl(struct hda_codec *codec, hda_nid_t nid,
			  const char *name, int idx, bool phantom_jack)
{
	struct hda_jack_tbl *jack;
	struct snd_kcontrol *kctl;
	int err, state;

	jack = snd_hda_jack_tbl_new(codec, nid);
	if (!jack)
		return 0;
	if (jack->kctl)
		return 0; /* already created */
	kctl = snd_kctl_jack_new(name, idx, codec);
	if (!kctl)
		return -ENOMEM;
	err = snd_hda_ctl_add(codec, nid, kctl);
	if (err < 0)
		return err;
	jack->kctl = kctl;
	jack->phantom_jack = !!phantom_jack;

	state = snd_hda_jack_detect(codec, nid);
	snd_kctl_jack_report(codec->bus->card, kctl, state);
#ifdef CONFIG_SND_HDA_INPUT_JACK
	if (!phantom_jack) {
		jack->type = get_input_jack_type(codec, nid);
		err = snd_jack_new(codec->bus->card, name, jack->type,
				   &jack->jack);
		if (err < 0)
			return err;
		jack->jack->private_data = jack;
		jack->jack->private_free = hda_free_jack_priv;
		snd_jack_report(jack->jack, state ? jack->type : 0);
	}
#endif
	return 0;
}