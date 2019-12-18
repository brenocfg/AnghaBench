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
struct TYPE_3__ {unsigned int channels; } ;
struct snd_pcm_plugin {TYPE_1__ src_format; scalar_t__ extra_data; } ;
struct rate_priv {TYPE_2__* channels; scalar_t__ pos; } ;
struct TYPE_4__ {scalar_t__ last_S2; scalar_t__ last_S1; } ;

/* Variables and functions */

__attribute__((used)) static void rate_init(struct snd_pcm_plugin *plugin)
{
	unsigned int channel;
	struct rate_priv *data = (struct rate_priv *)plugin->extra_data;
	data->pos = 0;
	for (channel = 0; channel < plugin->src_format.channels; channel++) {
		data->channels[channel].last_S1 = 0;
		data->channels[channel].last_S2 = 0;
	}
}