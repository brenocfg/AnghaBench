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
struct hdmi_spec_per_pin {int num_mux_nids; scalar_t__* mux_nids; } ;
struct hdmi_spec_per_cvt {scalar_t__ cvt_nid; scalar_t__ assigned; } ;
struct hdmi_spec {int num_cvts; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 int ENODEV ; 
 struct hdmi_spec_per_cvt* get_cvt (struct hdmi_spec*,int) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 

__attribute__((used)) static int hdmi_choose_cvt(struct hda_codec *codec,
			int pin_idx, int *cvt_id, int *mux_id)
{
	struct hdmi_spec *spec = codec->spec;
	struct hdmi_spec_per_pin *per_pin;
	struct hdmi_spec_per_cvt *per_cvt = NULL;
	int cvt_idx, mux_idx = 0;

	per_pin = get_pin(spec, pin_idx);

	/* Dynamically assign converter to stream */
	for (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++) {
		per_cvt = get_cvt(spec, cvt_idx);

		/* Must not already be assigned */
		if (per_cvt->assigned)
			continue;
		/* Must be in pin's mux's list of converters */
		for (mux_idx = 0; mux_idx < per_pin->num_mux_nids; mux_idx++)
			if (per_pin->mux_nids[mux_idx] == per_cvt->cvt_nid)
				break;
		/* Not in mux list */
		if (mux_idx == per_pin->num_mux_nids)
			continue;
		break;
	}

	/* No free converters */
	if (cvt_idx == spec->num_cvts)
		return -ENODEV;

	if (cvt_id)
		*cvt_id = cvt_idx;
	if (mux_id)
		*mux_id = mux_idx;

	return 0;
}