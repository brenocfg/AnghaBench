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
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {scalar_t__ dsp_state; int /*<<< orphan*/ * dacs; scalar_t__* effects_switch; } ;

/* Variables and functions */
 scalar_t__ DSP_DOWNLOADING ; 
 size_t EFFECT_START_NID ; 
 size_t PLAY_ENHANCEMENT ; 
 int /*<<< orphan*/  ca0132_cleanup_stream (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int ca0132_playback_pcm_cleanup(struct hda_pcm_stream *hinfo,
			struct hda_codec *codec,
			struct snd_pcm_substream *substream)
{
	struct ca0132_spec *spec = codec->spec;

	if (spec->dsp_state == DSP_DOWNLOADING)
		return 0;

	/*If Playback effects are on, allow stream some time to flush
	 *effects tail*/
	if (spec->effects_switch[PLAY_ENHANCEMENT - EFFECT_START_NID])
		msleep(50);

	ca0132_cleanup_stream(codec, spec->dacs[0]);

	return 0;
}