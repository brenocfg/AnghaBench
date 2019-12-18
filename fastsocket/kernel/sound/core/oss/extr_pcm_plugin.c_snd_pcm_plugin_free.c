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
struct snd_pcm_plugin {int /*<<< orphan*/  buf; struct snd_pcm_plugin* buf_channels; int /*<<< orphan*/  (* private_free ) (struct snd_pcm_plugin*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_pcm_plugin*) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_plugin*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

int snd_pcm_plugin_free(struct snd_pcm_plugin *plugin)
{
	if (! plugin)
		return 0;
	if (plugin->private_free)
		plugin->private_free(plugin);
	kfree(plugin->buf_channels);
	vfree(plugin->buf);
	kfree(plugin);
	return 0;
}