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
struct audio {int opened; int phys; int volume; int /*<<< orphan*/  lock; TYPE_1__* out; int /*<<< orphan*/ * data; scalar_t__ dec_id; int /*<<< orphan*/  audmgr; int /*<<< orphan*/  audplay; } ;
struct TYPE_2__ {int addr; int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int BUFSZ ; 
 int /*<<< orphan*/  DMASZ ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audamrnb_flush (struct audio*) ; 
 int /*<<< orphan*/  audmgr_disable (int /*<<< orphan*/ *) ; 
 int audmgr_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audplay_adsp_ops_amrnb ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int msm_adsp_get (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct audio*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct audio the_amrnb_audio ; 

__attribute__((used)) static int audamrnb_open(struct inode *inode, struct file *file)
{
	struct audio *audio = &the_amrnb_audio;
	int rc;

	mutex_lock(&audio->lock);

	if (audio->opened) {
		pr_err("audio: busy\n");
		rc = -EBUSY;
		goto done;
	}

	if (!audio->data) {
		audio->data = dma_alloc_coherent(NULL, DMASZ,
						 &audio->phys, GFP_KERNEL);
		if (!audio->data) {
			pr_err("audio: could not allocate DMA buffers\n");
			rc = -ENOMEM;
			goto done;
		}
	}

	rc = audmgr_open(&audio->audmgr);
	if (rc)
		goto done;

	rc = msm_adsp_get("AUDPLAY0TASK", &audio->audplay,
		&audplay_adsp_ops_amrnb, audio);
	if (rc) {
		pr_err("audio: failed to get audplay0 dsp module\n");
		audmgr_disable(&audio->audmgr);
		dma_free_coherent(NULL, DMASZ, audio->data, audio->phys);
		audio->data = NULL;
		goto done;
	}

	audio->dec_id = 0;

	audio->out[0].data = audio->data + 0;
	audio->out[0].addr = audio->phys + 0;
	audio->out[0].size = BUFSZ;

	audio->out[1].data = audio->data + BUFSZ;
	audio->out[1].addr = audio->phys + BUFSZ;
	audio->out[1].size = BUFSZ;

	audio->volume = 0x2000;	/* Q13 1.0 */

	audamrnb_flush(audio);

	file->private_data = audio;
	audio->opened = 1;
	rc = 0;
done:
	mutex_unlock(&audio->lock);
	return rc;
}