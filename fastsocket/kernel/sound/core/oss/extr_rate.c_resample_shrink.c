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
struct TYPE_6__ {int first; int step; scalar_t__ addr; } ;
struct snd_pcm_plugin_channel {int enabled; TYPE_3__ area; scalar_t__ wanted; } ;
struct TYPE_5__ {int /*<<< orphan*/  format; } ;
struct TYPE_4__ {unsigned int channels; } ;
struct snd_pcm_plugin {TYPE_2__ dst_format; TYPE_1__ src_format; scalar_t__ extra_data; } ;
struct rate_priv {unsigned int pos; scalar_t__ pitch; struct rate_channel* channels; } ;
struct rate_channel {short last_S1; short last_S2; } ;

/* Variables and functions */
 short BITS ; 
 unsigned int R_MASK ; 
 int /*<<< orphan*/  snd_pcm_area_silence (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resample_shrink(struct snd_pcm_plugin *plugin,
			    const struct snd_pcm_plugin_channel *src_channels,
			    struct snd_pcm_plugin_channel *dst_channels,
			    int src_frames, int dst_frames)
{
	unsigned int pos = 0;
	signed int val;
	signed short S1, S2;
	signed short *src, *dst;
	unsigned int channel;
	int src_step, dst_step;
	int src_frames1, dst_frames1;
	struct rate_priv *data = (struct rate_priv *)plugin->extra_data;
	struct rate_channel *rchannels = data->channels;

	for (channel = 0; channel < plugin->src_format.channels; ++channel) {
		pos = data->pos;
		S1 = rchannels->last_S1;
		S2 = rchannels->last_S2;
		if (!src_channels[channel].enabled) {
			if (dst_channels[channel].wanted)
				snd_pcm_area_silence(&dst_channels[channel].area, 0, dst_frames, plugin->dst_format.format);
			dst_channels[channel].enabled = 0;
			continue;
		}
		dst_channels[channel].enabled = 1;
		src = (signed short *)src_channels[channel].area.addr +
			src_channels[channel].area.first / 8 / 2;
		dst = (signed short *)dst_channels[channel].area.addr +
			dst_channels[channel].area.first / 8 / 2;
		src_step = src_channels[channel].area.step / 8 / 2;
		dst_step = dst_channels[channel].area.step / 8 / 2;
		src_frames1 = src_frames;
		dst_frames1 = dst_frames;
		while (dst_frames1 > 0) {
			S1 = S2;
			if (src_frames1-- > 0) {
				S2 = *src;
				src += src_step;
			}
			if (pos & ~R_MASK) {
				pos &= R_MASK;
				val = S1 + ((S2 - S1) * (signed int)pos) / BITS;
				if (val < -32768)
					val = -32768;
				else if (val > 32767)
					val = 32767;
				*dst = val;
				dst += dst_step;
				dst_frames1--;
			}
			pos += data->pitch;
		}
		rchannels->last_S1 = S1;
		rchannels->last_S2 = S2;
		rchannels++;
	}
	data->pos = pos;
}