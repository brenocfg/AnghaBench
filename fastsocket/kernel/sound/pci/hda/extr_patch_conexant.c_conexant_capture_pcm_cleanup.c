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
struct snd_pcm_substream {size_t number; } ;
struct hda_pcm_stream {int dummy; } ;
struct hda_codec {struct conexant_spec* spec; } ;
struct conexant_spec {int /*<<< orphan*/  (* capture_cleanup ) (struct hda_codec*) ;int /*<<< orphan*/ * adc_nids; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_codec_cleanup_stream (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*) ; 

__attribute__((used)) static int conexant_capture_pcm_cleanup(struct hda_pcm_stream *hinfo,
				      struct hda_codec *codec,
				      struct snd_pcm_substream *substream)
{
	struct conexant_spec *spec = codec->spec;
	snd_hda_codec_cleanup_stream(codec, spec->adc_nids[substream->number]);
	if (spec->capture_cleanup)
		spec->capture_cleanup(codec);
	return 0;
}