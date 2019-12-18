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
struct hdmi_spec_per_cvt {int /*<<< orphan*/  cvt_nid; } ;
struct hdmi_spec {int dummy; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 struct hdmi_spec_per_cvt* get_cvt (struct hdmi_spec*,int /*<<< orphan*/ ) ; 
 int simple_hdmi_build_jack (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int snd_hda_create_spdif_out_ctls (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simple_playback_build_controls(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_cvt *per_cvt;
	int err;

	per_cvt = get_cvt(spec, 0);
	err = snd_hda_create_spdif_out_ctls(codec, per_cvt->cvt_nid,
					    per_cvt->cvt_nid);
	if (err < 0)
		return err;
	return simple_hdmi_build_jack(codec, 0);
}