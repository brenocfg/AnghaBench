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
struct snd_pcm_plugin_format {scalar_t__ rate; scalar_t__ channels; int /*<<< orphan*/  format; } ;
struct snd_pcm_plugin {int /*<<< orphan*/  transfer; scalar_t__ extra_data; } ;
struct linear_priv {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  init_data (struct linear_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linear_transfer ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_pcm_format_linear (int /*<<< orphan*/ ) ; 
 int snd_pcm_plugin_build (struct snd_pcm_substream*,char*,struct snd_pcm_plugin_format*,struct snd_pcm_plugin_format*,int,struct snd_pcm_plugin**) ; 

int snd_pcm_plugin_build_linear(struct snd_pcm_substream *plug,
				struct snd_pcm_plugin_format *src_format,
				struct snd_pcm_plugin_format *dst_format,
				struct snd_pcm_plugin **r_plugin)
{
	int err;
	struct linear_priv *data;
	struct snd_pcm_plugin *plugin;

	if (snd_BUG_ON(!r_plugin))
		return -ENXIO;
	*r_plugin = NULL;

	if (snd_BUG_ON(src_format->rate != dst_format->rate))
		return -ENXIO;
	if (snd_BUG_ON(src_format->channels != dst_format->channels))
		return -ENXIO;
	if (snd_BUG_ON(!snd_pcm_format_linear(src_format->format) ||
		       !snd_pcm_format_linear(dst_format->format)))
		return -ENXIO;

	err = snd_pcm_plugin_build(plug, "linear format conversion",
				   src_format, dst_format,
				   sizeof(struct linear_priv), &plugin);
	if (err < 0)
		return err;
	data = (struct linear_priv *)plugin->extra_data;
	init_data(data, src_format->format, dst_format->format);
	plugin->transfer = linear_transfer;
	*r_plugin = plugin;
	return 0;
}