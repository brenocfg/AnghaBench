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
struct snd_usb_substream {int interface; struct snd_pcm_substream* pcm_substream; scalar_t__ altset_idx; } ;
struct snd_usb_stream {struct snd_usb_substream* substream; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_usb_substream* private_data; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int setup_hw_info (struct snd_pcm_runtime*,struct snd_usb_substream*) ; 
 struct snd_usb_stream* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_usb_hardware ; 

__attribute__((used)) static int snd_usb_pcm_open(struct snd_pcm_substream *substream, int direction)
{
	struct snd_usb_stream *as = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_usb_substream *subs = &as->substream[direction];

	subs->interface = -1;
	subs->altset_idx = 0;
	runtime->hw = snd_usb_hardware;
	runtime->private_data = subs;
	subs->pcm_substream = substream;
	/* runtime PM is also done there */
	return setup_hw_info(runtime, subs);
}