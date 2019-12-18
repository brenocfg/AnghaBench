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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_GEN_PCM_ACT_CLOSE ; 
 int /*<<< orphan*/  call_pcm_capture_hook (struct hda_pcm_stream*,struct hda_codec*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int capture_pcm_close(struct hda_pcm_stream *hinfo,
			     struct hda_codec *codec,
			     struct snd_pcm_substream *substream)
{
	call_pcm_capture_hook(hinfo, codec, substream, HDA_GEN_PCM_ACT_CLOSE);
	return 0;
}