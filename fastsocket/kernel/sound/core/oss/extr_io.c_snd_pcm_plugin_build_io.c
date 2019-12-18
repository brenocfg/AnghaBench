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
struct snd_pcm_plugin_format {int channels; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; } ;
struct snd_pcm_plugin {scalar_t__ access; int /*<<< orphan*/  transfer; int /*<<< orphan*/  client_channels; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ SNDRV_PCM_ACCESS_RW_INTERLEAVED ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  io_capture_transfer ; 
 int /*<<< orphan*/  io_playback_transfer ; 
 int /*<<< orphan*/  io_src_channels ; 
 scalar_t__ params_access (struct snd_pcm_hw_params*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 scalar_t__ snd_pcm_plug_stream (struct snd_pcm_substream*) ; 
 int snd_pcm_plugin_build (struct snd_pcm_substream*,char*,struct snd_pcm_plugin_format*,struct snd_pcm_plugin_format*,int,struct snd_pcm_plugin**) ; 

int snd_pcm_plugin_build_io(struct snd_pcm_substream *plug,
			    struct snd_pcm_hw_params *params,
			    struct snd_pcm_plugin **r_plugin)
{
	int err;
	struct snd_pcm_plugin_format format;
	struct snd_pcm_plugin *plugin;

	if (snd_BUG_ON(!r_plugin))
		return -ENXIO;
	*r_plugin = NULL;
	if (snd_BUG_ON(!plug || !params))
		return -ENXIO;
	format.format = params_format(params);
	format.rate = params_rate(params);
	format.channels = params_channels(params);
	err = snd_pcm_plugin_build(plug, "I/O io",
				   &format, &format,
				   sizeof(void *) * format.channels,
				   &plugin);
	if (err < 0)
		return err;
	plugin->access = params_access(params);
	if (snd_pcm_plug_stream(plug) == SNDRV_PCM_STREAM_PLAYBACK) {
		plugin->transfer = io_playback_transfer;
		if (plugin->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED)
			plugin->client_channels = io_src_channels;
	} else {
		plugin->transfer = io_capture_transfer;
	}

	*r_plugin = plugin;
	return 0;
}