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
struct hdmi_spec_per_pin {int /*<<< orphan*/  pin_nid; } ;
struct hdmi_spec {int dummy; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hdmi_str ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 TYPE_1__* get_pcm_rec (struct hdmi_spec*,int) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 int /*<<< orphan*/  is_jack_detectable (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_jack_add_kctl (struct hda_codec*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static int generic_hdmi_build_jack(struct hda_codec *codec, int pin_idx)
{
	char hdmi_str[32] = "HDMI/DP";
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
	int pcmdev = get_pcm_rec(spec, pin_idx)->device;

	if (pcmdev > 0)
		sprintf(hdmi_str + strlen(hdmi_str), ",pcm=%d", pcmdev);
	if (!is_jack_detectable(codec, per_pin->pin_nid))
		strncat(hdmi_str, " Phantom",
			sizeof(hdmi_str) - strlen(hdmi_str) - 1);

	return snd_hda_jack_add_kctl(codec, per_pin->pin_nid, hdmi_str, 0);
}