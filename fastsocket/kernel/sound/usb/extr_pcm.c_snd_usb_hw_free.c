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
struct snd_usb_substream {TYPE_2__* stream; scalar_t__ period_bytes; scalar_t__ cur_rate; int /*<<< orphan*/ * cur_audiofmt; } ;
struct snd_pcm_substream {TYPE_3__* runtime; } ;
struct TYPE_6__ {struct snd_usb_substream* private_data; } ;
struct TYPE_5__ {TYPE_1__* chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  shutdown_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  deactivate_endpoints (struct snd_usb_substream*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int snd_pcm_lib_free_vmalloc_buffer (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stop_endpoints (struct snd_usb_substream*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int snd_usb_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_usb_substream *subs = substream->runtime->private_data;

	subs->cur_audiofmt = NULL;
	subs->cur_rate = 0;
	subs->period_bytes = 0;
	mutex_lock(&subs->stream->chip->shutdown_mutex);
	stop_endpoints(subs, 0, 1, 1);
	deactivate_endpoints(subs);
	mutex_unlock(&subs->stream->chip->shutdown_mutex);
	return snd_pcm_lib_free_vmalloc_buffer(substream);
}