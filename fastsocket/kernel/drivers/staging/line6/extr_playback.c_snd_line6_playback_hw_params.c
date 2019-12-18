#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* pcm; int /*<<< orphan*/ * private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_line6_pcm {int /*<<< orphan*/  wrap_out; int /*<<< orphan*/  period_out; } ;
struct TYPE_2__ {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LINE6_ISO_PACKET_SIZE_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  s2m (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct snd_line6_pcm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_line6_playback_hw_params(struct snd_pcm_substream *substream, struct snd_pcm_hw_params *hw_params)
{
	int ret;
	struct snd_line6_pcm *line6pcm = snd_pcm_substream_chip(substream);

	/* -- Florian Demski [FD] */
	/* don't ask me why, but this fixes the bug on my machine */
	if (line6pcm == NULL) {
		if (substream->pcm == NULL)
			return -ENOMEM;
		if (substream->pcm->private_data == NULL)
			return -ENOMEM;
		substream->private_data = substream->pcm->private_data;
		line6pcm = snd_pcm_substream_chip(substream);
	}
	/* -- [FD] end */

	ret = snd_pcm_lib_malloc_pages(substream,
				       params_buffer_bytes(hw_params));
	if (ret < 0)
		return ret;

	line6pcm->period_out = params_period_bytes(hw_params);
	line6pcm->wrap_out = kmalloc(2 * LINE6_ISO_PACKET_SIZE_MAX, GFP_KERNEL);

	if (!line6pcm->wrap_out) {
		dev_err(s2m(substream), "cannot malloc wrap_out\n");
		return -ENOMEM;
	}

	return 0;
}