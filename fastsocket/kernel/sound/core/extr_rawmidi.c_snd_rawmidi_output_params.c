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
struct snd_rawmidi_substream {int use_count; int active_sensing; scalar_t__ append; struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {int buffer_size; char* buffer; int avail; int avail_min; } ;
struct snd_rawmidi_params {int buffer_size; int avail_min; int /*<<< orphan*/  no_active_sensing; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_drain_output (struct snd_rawmidi_substream*) ; 

int snd_rawmidi_output_params(struct snd_rawmidi_substream *substream,
			      struct snd_rawmidi_params * params)
{
	char *newbuf;
	struct snd_rawmidi_runtime *runtime = substream->runtime;
	
	if (substream->append && substream->use_count > 1)
		return -EBUSY;
	snd_rawmidi_drain_output(substream);
	if (params->buffer_size < 32 || params->buffer_size > 1024L * 1024L) {
		return -EINVAL;
	}
	if (params->avail_min < 1 || params->avail_min > params->buffer_size) {
		return -EINVAL;
	}
	if (params->buffer_size != runtime->buffer_size) {
		newbuf = kmalloc(params->buffer_size, GFP_KERNEL);
		if (!newbuf)
			return -ENOMEM;
		kfree(runtime->buffer);
		runtime->buffer = newbuf;
		runtime->buffer_size = params->buffer_size;
		runtime->avail = runtime->buffer_size;
	}
	runtime->avail_min = params->avail_min;
	substream->active_sensing = !params->no_active_sensing;
	return 0;
}