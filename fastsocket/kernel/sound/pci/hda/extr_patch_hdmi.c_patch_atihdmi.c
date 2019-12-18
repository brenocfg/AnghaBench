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
struct TYPE_3__ {int /*<<< orphan*/  prepare; } ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct hdmi_spec {TYPE_2__ pcm_playback; } ;
struct hda_codec {struct hdmi_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIHDMI_CVT_NID ; 
 int /*<<< orphan*/  ATIHDMI_PIN_NID ; 
 int /*<<< orphan*/  atihdmi_playback_pcm_prepare ; 
 int patch_simple_hdmi (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_atihdmi(struct hda_codec *codec)
{
	struct hdmi_spec *spec;
	int err = patch_simple_hdmi(codec, ATIHDMI_CVT_NID, ATIHDMI_PIN_NID);
	if (err < 0)
		return err;
	spec = codec->spec;
	spec->pcm_playback.ops.prepare = atihdmi_playback_pcm_prepare;
	return 0;
}