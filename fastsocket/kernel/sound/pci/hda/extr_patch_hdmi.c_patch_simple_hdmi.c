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
struct hdmi_spec_per_pin {void* pin_nid; } ;
struct hdmi_spec_per_cvt {void* cvt_nid; } ;
struct TYPE_2__ {int max_channels; void* dig_out_nid; scalar_t__ num_dacs; } ;
struct hdmi_spec {int num_cvts; int num_pins; int /*<<< orphan*/  pcm_playback; int /*<<< orphan*/  cvts; int /*<<< orphan*/  pins; TYPE_1__ multiout; } ;
struct hda_codec {int /*<<< orphan*/  patch_ops; struct hdmi_spec* spec; } ;
typedef  void* hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hdmi_array_init (struct hdmi_spec*,int) ; 
 struct hdmi_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_hdmi_patch_ops ; 
 int /*<<< orphan*/  simple_pcm_playback ; 
 int /*<<< orphan*/  simple_playback_free (struct hda_codec*) ; 
 void* snd_array_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int patch_simple_hdmi(struct hda_codec *codec,
			     hda_nid_t cvt_nid, hda_nid_t pin_nid)
{
	struct hdmi_spec *spec;
	struct hdmi_spec_per_cvt *per_cvt;
	struct hdmi_spec_per_pin *per_pin;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;

	codec->spec = spec;
	hdmi_array_init(spec, 1);

	spec->multiout.num_dacs = 0;  /* no analog */
	spec->multiout.max_channels = 2;
	spec->multiout.dig_out_nid = cvt_nid;
	spec->num_cvts = 1;
	spec->num_pins = 1;
	per_pin = snd_array_new(&spec->pins);
	per_cvt = snd_array_new(&spec->cvts);
	if (!per_pin || !per_cvt) {
		simple_playback_free(codec);
		return -ENOMEM;
	}
	per_cvt->cvt_nid = cvt_nid;
	per_pin->pin_nid = pin_nid;
	spec->pcm_playback = simple_pcm_playback;

	codec->patch_ops = simple_hdmi_patch_ops;

	return 0;
}