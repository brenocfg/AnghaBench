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
struct hdmi_eld {int dummy; } ;
struct hdmi_spec_per_pin {int /*<<< orphan*/  work; struct hdmi_eld sink_eld; } ;
struct hdmi_spec {int num_pins; } ;
struct hda_codec {TYPE_1__* bus; struct hdmi_spec* spec; } ;
struct TYPE_2__ {int /*<<< orphan*/  workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 int /*<<< orphan*/  hdmi_array_free (struct hdmi_spec*) ; 
 int /*<<< orphan*/  kfree (struct hdmi_spec*) ; 
 int /*<<< orphan*/  snd_hda_eld_proc_free (struct hda_codec*,struct hdmi_eld*) ; 

__attribute__((used)) static void generic_hdmi_free(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;
	int pin_idx;

	for (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		struct hdmi_spec_per_pin *per_pin = get_pin(spec, pin_idx);
		struct hdmi_eld *eld = &per_pin->sink_eld;

		cancel_delayed_work(&per_pin->work);
		snd_hda_eld_proc_free(codec, eld);
	}

	flush_workqueue(codec->bus->workq);
	hdmi_array_free(spec);
	kfree(spec);
}