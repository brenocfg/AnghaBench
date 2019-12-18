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
struct inode {int dummy; } ;
struct file {struct audio_in* private_data; } ;
struct audio_in {int /*<<< orphan*/  lock; scalar_t__ opened; int /*<<< orphan*/ * audpre; int /*<<< orphan*/ * audrec; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_flush (struct audio_in*) ; 
 int /*<<< orphan*/  audio_in_disable (struct audio_in*) ; 
 int /*<<< orphan*/  msm_adsp_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audio_in_release(struct inode *inode, struct file *file)
{
	struct audio_in *audio = file->private_data;

	mutex_lock(&audio->lock);
	audio_in_disable(audio);
	audio_flush(audio);
	msm_adsp_put(audio->audrec);
	msm_adsp_put(audio->audpre);
	audio->audrec = NULL;
	audio->audpre = NULL;
	audio->opened = 0;
	mutex_unlock(&audio->lock);
	return 0;
}