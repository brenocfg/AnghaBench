#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sw_kctl; } ;
struct hda_gen_spec {TYPE_2__ vmaster_mute; scalar_t__ auto_mute_via_amp; int /*<<< orphan*/  (* automute_hook ) (struct hda_codec*) ;} ;
struct hda_codec {TYPE_1__* bus; struct hda_gen_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ctl_sync_vmaster (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_gen_update_outputs (struct hda_codec*) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 

__attribute__((used)) static void call_update_outputs(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	if (spec->automute_hook)
		spec->automute_hook(codec);
	else
		snd_hda_gen_update_outputs(codec);

	/* sync the whole vmaster slaves to reflect the new auto-mute status */
	if (spec->auto_mute_via_amp && !codec->bus->shutdown)
		snd_ctl_sync_vmaster(spec->vmaster_mute.sw_kctl, false);
}