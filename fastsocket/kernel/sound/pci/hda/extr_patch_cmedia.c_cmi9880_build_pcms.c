#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hda_pcm {char* name; TYPE_2__* stream; int /*<<< orphan*/  pcm_type; } ;
struct hda_codec {int num_pcms; struct hda_pcm* pcm_info; struct cmi_spec* spec; } ;
struct TYPE_6__ {scalar_t__ dig_out_nid; } ;
struct cmi_spec {scalar_t__ dig_in_nid; TYPE_1__ multiout; struct hda_pcm* pcm_rec; } ;
struct TYPE_7__ {scalar_t__ nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_PCM_TYPE_SPDIF ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_2__ cmi9880_pcm_analog_capture ; 
 TYPE_2__ cmi9880_pcm_analog_playback ; 
 TYPE_2__ cmi9880_pcm_digital_capture ; 
 TYPE_2__ cmi9880_pcm_digital_playback ; 

__attribute__((used)) static int cmi9880_build_pcms(struct hda_codec *codec)
{
	struct cmi_spec *spec = codec->spec;
	struct hda_pcm *info = spec->pcm_rec;

	codec->num_pcms = 1;
	codec->pcm_info = info;

	info->name = "CMI9880";
	info->stream[SNDRV_PCM_STREAM_PLAYBACK] = cmi9880_pcm_analog_playback;
	info->stream[SNDRV_PCM_STREAM_CAPTURE] = cmi9880_pcm_analog_capture;

	if (spec->multiout.dig_out_nid || spec->dig_in_nid) {
		codec->num_pcms++;
		info++;
		info->name = "CMI9880 Digital";
		info->pcm_type = HDA_PCM_TYPE_SPDIF;
		if (spec->multiout.dig_out_nid) {
			info->stream[SNDRV_PCM_STREAM_PLAYBACK] = cmi9880_pcm_digital_playback;
			info->stream[SNDRV_PCM_STREAM_PLAYBACK].nid = spec->multiout.dig_out_nid;
		}
		if (spec->dig_in_nid) {
			info->stream[SNDRV_PCM_STREAM_CAPTURE] = cmi9880_pcm_digital_capture;
			info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = spec->dig_in_nid;
		}
	}

	return 0;
}