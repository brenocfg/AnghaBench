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
struct file {struct audio* private_data; } ;
struct audio {int /*<<< orphan*/  lock; scalar_t__ opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_OPEN ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWRSINK_AUDIO ; 
 int /*<<< orphan*/  audio_disable (struct audio*) ; 
 int /*<<< orphan*/  audio_flush (struct audio*) ; 
 int /*<<< orphan*/  htc_pwrsink_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int audio_release(struct inode *inode, struct file *file)
{
	struct audio *audio = file->private_data;

	LOG(EV_OPEN, 0);
	mutex_lock(&audio->lock);
	audio_disable(audio);
	audio_flush(audio);
	audio->opened = 0;
	mutex_unlock(&audio->lock);
	htc_pwrsink_set(PWRSINK_AUDIO, 0);
	return 0;
}