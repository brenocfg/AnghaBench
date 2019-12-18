#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
struct snd_pcm_file {int dummy; } ;
struct snd_pcm {TYPE_1__* card; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  open_wait; } ;
struct file {int f_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  module; scalar_t__ shutdown; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EFAULT ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int snd_card_file_add (TYPE_1__*,struct file*) ; 
 int /*<<< orphan*/  snd_card_file_remove (TYPE_1__*,struct file*) ; 
 int snd_pcm_open_file (struct file*,struct snd_pcm*,int,struct snd_pcm_file**) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_pcm_open(struct file *file, struct snd_pcm *pcm, int stream)
{
	int err;
	struct snd_pcm_file *pcm_file;
	wait_queue_t wait;

	if (pcm == NULL) {
		err = -ENODEV;
		goto __error1;
	}
	err = snd_card_file_add(pcm->card, file);
	if (err < 0)
		goto __error1;
	if (!try_module_get(pcm->card->module)) {
		err = -EFAULT;
		goto __error2;
	}
	init_waitqueue_entry(&wait, current);
	add_wait_queue(&pcm->open_wait, &wait);
	mutex_lock(&pcm->open_mutex);
	while (1) {
		err = snd_pcm_open_file(file, pcm, stream, &pcm_file);
		if (err >= 0)
			break;
		if (err == -EAGAIN) {
			if (file->f_flags & O_NONBLOCK) {
				err = -EBUSY;
				break;
			}
		} else
			break;
		set_current_state(TASK_INTERRUPTIBLE);
		mutex_unlock(&pcm->open_mutex);
		schedule();
		mutex_lock(&pcm->open_mutex);
		if (pcm->card->shutdown) {
			err = -ENODEV;
			break;
		}
		if (signal_pending(current)) {
			err = -ERESTARTSYS;
			break;
		}
	}
	remove_wait_queue(&pcm->open_wait, &wait);
	mutex_unlock(&pcm->open_mutex);
	if (err < 0)
		goto __error;
	return err;

      __error:
	module_put(pcm->card->module);
      __error2:
      	snd_card_file_remove(pcm->card, file);
      __error1:
      	return err;
}