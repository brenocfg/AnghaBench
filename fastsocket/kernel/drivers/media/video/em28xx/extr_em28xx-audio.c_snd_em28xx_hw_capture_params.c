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
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 unsigned int params_channels (struct snd_pcm_hw_params*) ; 
 unsigned int params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int snd_pcm_alloc_vmalloc_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_em28xx_hw_capture_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *hw_params)
{
	unsigned int channels, rate, format;
	int ret;

	dprintk("Setting capture parameters\n");

	ret = snd_pcm_alloc_vmalloc_buffer(substream,
				params_buffer_bytes(hw_params));
	format = params_format(hw_params);
	rate = params_rate(hw_params);
	channels = params_channels(hw_params);

	/* TODO: set up em28xx audio chip to deliver the correct audio format,
	   current default is 48000hz multiplexed => 96000hz mono
	   which shouldn't matter since analogue TV only supports mono */
	return 0;
}