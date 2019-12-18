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
struct hdmi_spec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_power_state; } ;
struct hda_codec {int vendor_id; TYPE_1__ patch_ops; struct hdmi_spec* spec; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  generic_hdmi_init_per_pins (struct hda_codec*) ; 
 TYPE_1__ generic_hdmi_patch_ops ; 
 int /*<<< orphan*/  haswell_set_power_state ; 
 int /*<<< orphan*/  hdmi_array_init (struct hdmi_spec*,int) ; 
 scalar_t__ hdmi_parse_codec (struct hda_codec*) ; 
 int /*<<< orphan*/  init_channel_allocations () ; 
 int /*<<< orphan*/  intel_haswell_enable_all_pins (struct hda_codec*,int) ; 
 int /*<<< orphan*/  intel_haswell_fixup_enable_dp12 (struct hda_codec*) ; 
 int /*<<< orphan*/  kfree (struct hdmi_spec*) ; 
 struct hdmi_spec* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_generic_hdmi(struct hda_codec *codec)
{
	struct hdmi_spec *spec;

	spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (spec == NULL)
		return -ENOMEM;

	codec->spec = spec;
	hdmi_array_init(spec, 4);

	if (codec->vendor_id == 0x80862807) {
		intel_haswell_enable_all_pins(codec, true);
		intel_haswell_fixup_enable_dp12(codec);
	}

	if (hdmi_parse_codec(codec) < 0) {
		codec->spec = NULL;
		kfree(spec);
		return -EINVAL;
	}
	codec->patch_ops = generic_hdmi_patch_ops;
	if (codec->vendor_id == 0x80862807)
		codec->patch_ops.set_power_state = haswell_set_power_state;

	generic_hdmi_init_per_pins(codec);

	init_channel_allocations();

	return 0;
}