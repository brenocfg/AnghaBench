#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* addr; int first; int step; } ;
struct snd_pcm_plugin_channel {int enabled; TYPE_3__ area; scalar_t__ wanted; } ;
struct TYPE_5__ {int /*<<< orphan*/  format; } ;
struct TYPE_4__ {int channels; } ;
struct snd_pcm_plugin {TYPE_2__ dst_format; TYPE_1__ src_format; scalar_t__ extra_data; } ;
struct mulaw_priv {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 short cvt_native_to_s16 (struct mulaw_priv*,char*) ; 
 char linear2ulaw (short) ; 
 int /*<<< orphan*/  snd_pcm_area_silence (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mulaw_encode(struct snd_pcm_plugin *plugin,
			const struct snd_pcm_plugin_channel *src_channels,
			struct snd_pcm_plugin_channel *dst_channels,
			snd_pcm_uframes_t frames)
{
	struct mulaw_priv *data = (struct mulaw_priv *)plugin->extra_data;
	int channel;
	int nchannels = plugin->src_format.channels;
	for (channel = 0; channel < nchannels; ++channel) {
		char *src;
		char *dst;
		int src_step, dst_step;
		snd_pcm_uframes_t frames1;
		if (!src_channels[channel].enabled) {
			if (dst_channels[channel].wanted)
				snd_pcm_area_silence(&dst_channels[channel].area, 0, frames, plugin->dst_format.format);
			dst_channels[channel].enabled = 0;
			continue;
		}
		dst_channels[channel].enabled = 1;
		src = src_channels[channel].area.addr + src_channels[channel].area.first / 8;
		dst = dst_channels[channel].area.addr + dst_channels[channel].area.first / 8;
		src_step = src_channels[channel].area.step / 8;
		dst_step = dst_channels[channel].area.step / 8;
		frames1 = frames;
		while (frames1-- > 0) {
			signed short sample = cvt_native_to_s16(data, src);
			*dst = linear2ulaw(sample);
			src += src_step;
			dst += dst_step;
		}
	}
}