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
struct hda_codec {struct cmi_spec* spec; } ;
struct cmi_spec {int /*<<< orphan*/  multiout; } ;

/* Variables and functions */
 int snd_hda_multi_out_analog_open (struct hda_codec*,int /*<<< orphan*/ *,struct snd_pcm_substream*,struct hda_pcm_stream*) ; 

__attribute__((used)) static int cmi9880_playback_pcm_open(struct hda_pcm_stream *hinfo,
				     struct hda_codec *codec,
				     struct snd_pcm_substream *substream)
{
	struct cmi_spec *spec = codec->spec;
	return snd_hda_multi_out_analog_open(codec, &spec->multiout, substream,
					     hinfo);
}