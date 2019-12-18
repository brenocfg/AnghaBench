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
struct ca0132_spec {int /*<<< orphan*/ * dacs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ca0132_setup_stream (struct hda_codec*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ca0132_playback_pcm_prepare(struct hda_pcm_stream *hinfo,
			struct hda_codec *codec,
			unsigned int stream_tag,
			unsigned int format,
			struct snd_pcm_substream *substream)
{
	struct ca0132_spec *spec = codec->spec;

	ca0132_setup_stream(codec, spec->dacs[0], stream_tag, 0, format);

	return 0;
}