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
struct hdmi_spec_per_pin {int /*<<< orphan*/  pcm_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct hdmi_spec {int num_pins; TYPE_1__ pcm_rec; } ;
struct hda_pcm_stream {int substreams; int /*<<< orphan*/  ops; } ;
struct hda_pcm {struct hda_pcm_stream* stream; int /*<<< orphan*/  pcm_type; int /*<<< orphan*/  name; } ;
struct hda_codec {int num_pcms; int /*<<< orphan*/  pcm_info; struct hdmi_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HDA_PCM_TYPE_HDMI ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  generic_ops ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 struct hda_pcm* snd_array_new (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int generic_hdmi_build_pcms(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;
	int pin_idx;

	for (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		struct hda_pcm *info;
		struct hda_pcm_stream *pstr;
		struct hdmi_spec_per_pin *per_pin;

		per_pin = get_pin(spec, pin_idx);
		sprintf(per_pin->pcm_name, "HDMI %d", pin_idx);
		info = snd_array_new(&spec->pcm_rec);
		if (!info)
			return -ENOMEM;
		info->name = per_pin->pcm_name;
		info->pcm_type = HDA_PCM_TYPE_HDMI;

		pstr = &info->stream[SNDRV_PCM_STREAM_PLAYBACK];
		pstr->substreams = 1;
		pstr->ops = generic_ops;
		/* other pstr fields are set in open */
	}

	codec->num_pcms = spec->num_pins;
	codec->pcm_info = spec->pcm_rec.list;

	return 0;
}