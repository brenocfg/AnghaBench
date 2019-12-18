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
struct snd_pcm_substream {int ref_count; int hw_opened; TYPE_1__* ops; } ;
struct snd_pcm {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int (* open ) (struct snd_pcm_substream*) ;} ;

/* Variables and functions */
 int snd_pcm_attach_substream (struct snd_pcm*,int,struct file*,struct snd_pcm_substream**) ; 
 int snd_pcm_hw_constraints_complete (struct snd_pcm_substream*) ; 
 int snd_pcm_hw_constraints_init (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_release_substream (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printd (char*) ; 
 int stub1 (struct snd_pcm_substream*) ; 

int snd_pcm_open_substream(struct snd_pcm *pcm, int stream,
			   struct file *file,
			   struct snd_pcm_substream **rsubstream)
{
	struct snd_pcm_substream *substream;
	int err;

	err = snd_pcm_attach_substream(pcm, stream, file, &substream);
	if (err < 0)
		return err;
	if (substream->ref_count > 1) {
		*rsubstream = substream;
		return 0;
	}

	err = snd_pcm_hw_constraints_init(substream);
	if (err < 0) {
		snd_printd("snd_pcm_hw_constraints_init failed\n");
		goto error;
	}

	if ((err = substream->ops->open(substream)) < 0)
		goto error;

	substream->hw_opened = 1;

	err = snd_pcm_hw_constraints_complete(substream);
	if (err < 0) {
		snd_printd("snd_pcm_hw_constraints_complete failed\n");
		goto error;
	}

	*rsubstream = substream;
	return 0;

 error:
	snd_pcm_release_substream(substream);
	return err;
}