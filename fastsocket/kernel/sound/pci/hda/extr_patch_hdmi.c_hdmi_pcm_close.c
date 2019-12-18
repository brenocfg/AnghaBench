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
struct snd_pcm_substream {int dummy; } ;
struct hdmi_spec_per_pin {int dummy; } ;
struct hdmi_spec_per_cvt {scalar_t__ assigned; } ;
struct hdmi_spec {int dummy; } ;
struct hda_pcm_stream {int /*<<< orphan*/  nid; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 int EINVAL ; 
 int cvt_nid_to_cvt_index (struct hdmi_spec*,int /*<<< orphan*/ ) ; 
 struct hdmi_spec_per_cvt* get_cvt (struct hdmi_spec*,int) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 int hinfo_to_pin_index (struct hdmi_spec*,struct hda_pcm_stream*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_hda_spdif_ctls_unassign (struct hda_codec*,int) ; 

__attribute__((used)) static int hdmi_pcm_close(struct hda_pcm_stream *hinfo,
			  struct hda_codec *codec,
			  struct snd_pcm_substream *substream)
{
	struct hdmi_spec *spec = codec->spec;
	int cvt_idx, pin_idx;
	struct hdmi_spec_per_cvt *per_cvt;
	struct hdmi_spec_per_pin *per_pin;

	if (hinfo->nid) {
		cvt_idx = cvt_nid_to_cvt_index(spec, hinfo->nid);
		if (snd_BUG_ON(cvt_idx < 0))
			return -EINVAL;
		per_cvt = get_cvt(spec, cvt_idx);

		snd_BUG_ON(!per_cvt->assigned);
		per_cvt->assigned = 0;
		hinfo->nid = 0;

		pin_idx = hinfo_to_pin_index(spec, hinfo);
		if (snd_BUG_ON(pin_idx < 0))
			return -EINVAL;
		per_pin = get_pin(spec, pin_idx);

		snd_hda_spdif_ctls_unassign(codec, pin_idx);
	}
	return 0;
}