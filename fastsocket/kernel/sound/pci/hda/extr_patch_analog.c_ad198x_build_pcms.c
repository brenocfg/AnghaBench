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
struct hda_codec {int num_pcms; int spdif_status_reset; struct hda_pcm* pcm_info; struct ad198x_spec* spec; } ;
struct TYPE_6__ {scalar_t__ dig_out_nid; scalar_t__* dac_nids; int /*<<< orphan*/  max_channels; } ;
struct ad198x_spec {scalar_t__ dig_in_nid; TYPE_1__ multiout; scalar_t__* adc_nids; int /*<<< orphan*/  num_adc_nids; struct hda_pcm* pcm_rec; } ;
struct TYPE_7__ {scalar_t__ nid; int /*<<< orphan*/  substreams; int /*<<< orphan*/  channels_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_PCM_TYPE_SPDIF ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_2__ ad198x_pcm_analog_capture ; 
 TYPE_2__ ad198x_pcm_analog_playback ; 
 TYPE_2__ ad198x_pcm_digital_capture ; 
 TYPE_2__ ad198x_pcm_digital_playback ; 

__attribute__((used)) static int ad198x_build_pcms(struct hda_codec *codec)
{
	struct ad198x_spec *spec = codec->spec;
	struct hda_pcm *info = spec->pcm_rec;

	codec->num_pcms = 1;
	codec->pcm_info = info;

	info->name = "AD198x Analog";
	info->stream[SNDRV_PCM_STREAM_PLAYBACK] = ad198x_pcm_analog_playback;
	info->stream[SNDRV_PCM_STREAM_PLAYBACK].channels_max = spec->multiout.max_channels;
	info->stream[SNDRV_PCM_STREAM_PLAYBACK].nid = spec->multiout.dac_nids[0];
	info->stream[SNDRV_PCM_STREAM_CAPTURE] = ad198x_pcm_analog_capture;
	info->stream[SNDRV_PCM_STREAM_CAPTURE].substreams = spec->num_adc_nids;
	info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = spec->adc_nids[0];

	if (spec->multiout.dig_out_nid) {
		info++;
		codec->num_pcms++;
		codec->spdif_status_reset = 1;
		info->name = "AD198x Digital";
		info->pcm_type = HDA_PCM_TYPE_SPDIF;
		info->stream[SNDRV_PCM_STREAM_PLAYBACK] = ad198x_pcm_digital_playback;
		info->stream[SNDRV_PCM_STREAM_PLAYBACK].nid = spec->multiout.dig_out_nid;
		if (spec->dig_in_nid) {
			info->stream[SNDRV_PCM_STREAM_CAPTURE] = ad198x_pcm_digital_capture;
			info->stream[SNDRV_PCM_STREAM_CAPTURE].nid = spec->dig_in_nid;
		}
	}

	return 0;
}