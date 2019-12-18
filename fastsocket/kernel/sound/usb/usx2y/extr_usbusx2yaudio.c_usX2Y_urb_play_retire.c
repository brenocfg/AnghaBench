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
struct urb {int actual_length; } ;
struct snd_usX2Y_substream {scalar_t__ transfer_done; scalar_t__ hwptr_done; TYPE_2__* pcm_substream; TYPE_1__* usX2Y; } ;
struct snd_pcm_runtime {scalar_t__ buffer_size; scalar_t__ period_size; } ;
struct TYPE_4__ {struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {int stride; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_period_elapsed (TYPE_2__*) ; 

__attribute__((used)) static void usX2Y_urb_play_retire(struct snd_usX2Y_substream *subs, struct urb *urb)
{
	struct snd_pcm_runtime *runtime = subs->pcm_substream->runtime;
	int		len = urb->actual_length / subs->usX2Y->stride;

	subs->transfer_done += len;
	subs->hwptr_done +=  len;
	if (subs->hwptr_done >= runtime->buffer_size)
		subs->hwptr_done -= runtime->buffer_size;
	if (subs->transfer_done >= runtime->period_size) {
		subs->transfer_done -= runtime->period_size;
		snd_pcm_period_elapsed(subs->pcm_substream);
	}
}