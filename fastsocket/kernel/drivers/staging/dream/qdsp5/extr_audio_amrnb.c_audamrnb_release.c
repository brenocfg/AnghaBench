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
struct inode {int dummy; } ;
struct file {struct audio* private_data; } ;
struct audio {int pcm_buf_count; int /*<<< orphan*/  lock; scalar_t__ pcm_feedback; int /*<<< orphan*/ * read_data; int /*<<< orphan*/  read_phys; TYPE_1__* in; int /*<<< orphan*/ * data; int /*<<< orphan*/  phys; scalar_t__ opened; int /*<<< orphan*/ * audplay; } ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int DMASZ ; 
 int /*<<< orphan*/  audamrnb_disable (struct audio*) ; 
 int /*<<< orphan*/  audamrnb_flush (struct audio*) ; 
 int /*<<< orphan*/  audamrnb_flush_pcm_buf (struct audio*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  msm_adsp_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audamrnb_release(struct inode *inode, struct file *file)
{
	struct audio *audio = file->private_data;

	dprintk("audamrnb_release()\n");

	mutex_lock(&audio->lock);
	audamrnb_disable(audio);
	audamrnb_flush(audio);
	audamrnb_flush_pcm_buf(audio);
	msm_adsp_put(audio->audplay);
	audio->audplay = NULL;
	audio->opened = 0;
	dma_free_coherent(NULL, DMASZ, audio->data, audio->phys);
	audio->data = NULL;
	if (audio->read_data != NULL) {
		dma_free_coherent(NULL,
				  audio->in[0].size * audio->pcm_buf_count,
				  audio->read_data, audio->read_phys);
		audio->read_data = NULL;
	}
	audio->pcm_feedback = 0;
	mutex_unlock(&audio->lock);
	return 0;
}