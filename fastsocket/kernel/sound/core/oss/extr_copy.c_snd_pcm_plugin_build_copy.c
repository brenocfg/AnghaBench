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
struct snd_pcm_plugin_format {scalar_t__ format; scalar_t__ rate; scalar_t__ channels; } ;
struct snd_pcm_plugin {int /*<<< orphan*/  transfer; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  copy_transfer ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_pcm_format_physical_width (scalar_t__) ; 
 int snd_pcm_plugin_build (struct snd_pcm_substream*,char*,struct snd_pcm_plugin_format*,struct snd_pcm_plugin_format*,int /*<<< orphan*/ ,struct snd_pcm_plugin**) ; 

int snd_pcm_plugin_build_copy(struct snd_pcm_substream *plug,
			      struct snd_pcm_plugin_format *src_format,
			      struct snd_pcm_plugin_format *dst_format,
			      struct snd_pcm_plugin **r_plugin)
{
	int err;
	struct snd_pcm_plugin *plugin;
	int width;

	if (snd_BUG_ON(!r_plugin))
		return -ENXIO;
	*r_plugin = NULL;

	if (snd_BUG_ON(src_format->format != dst_format->format))
		return -ENXIO;
	if (snd_BUG_ON(src_format->rate != dst_format->rate))
		return -ENXIO;
	if (snd_BUG_ON(src_format->channels != dst_format->channels))
		return -ENXIO;

	width = snd_pcm_format_physical_width(src_format->format);
	if (snd_BUG_ON(width <= 0))
		return -ENXIO;

	err = snd_pcm_plugin_build(plug, "copy", src_format, dst_format,
				   0, &plugin);
	if (err < 0)
		return err;
	plugin->transfer = copy_transfer;
	*r_plugin = plugin;
	return 0;
}