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
typedef  int /*<<< orphan*/  task_name ;
struct snd_pcm_oss_setup {int dummy; } ;
struct snd_pcm_oss_file {int dummy; } ;
struct snd_pcm {TYPE_1__* card; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  open_wait; } ;
struct inode {int dummy; } ;
struct file {int f_mode; int f_flags; } ;
typedef  int /*<<< orphan*/  setup ;
struct TYPE_3__ {int /*<<< orphan*/  module; scalar_t__ shutdown; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EFAULT ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SNDRV_OSS_DEVICE_TYPE_PCM ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct snd_pcm_oss_setup*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nonblock_open ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int snd_card_file_add (TYPE_1__*,struct file*) ; 
 int /*<<< orphan*/  snd_card_file_remove (TYPE_1__*,struct file*) ; 
 struct snd_pcm* snd_lookup_oss_minor_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_oss_look_for_setup (struct snd_pcm*,int /*<<< orphan*/ ,char*,struct snd_pcm_oss_setup*) ; 
 int snd_pcm_oss_open_file (struct file*,struct snd_pcm*,struct snd_pcm_oss_file**,int /*<<< orphan*/ ,struct snd_pcm_oss_setup*) ; 
 scalar_t__ snd_task_name (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_pcm_oss_open(struct inode *inode, struct file *file)
{
	int err;
	char task_name[32];
	struct snd_pcm *pcm;
	struct snd_pcm_oss_file *pcm_oss_file;
	struct snd_pcm_oss_setup setup[2];
	int nonblock;
	wait_queue_t wait;

	err = nonseekable_open(inode, file);
	if (err < 0)
		return err;

	pcm = snd_lookup_oss_minor_data(iminor(inode),
					SNDRV_OSS_DEVICE_TYPE_PCM);
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
	if (snd_task_name(current, task_name, sizeof(task_name)) < 0) {
		err = -EFAULT;
		goto __error;
	}
	memset(setup, 0, sizeof(setup));
	if (file->f_mode & FMODE_WRITE)
		snd_pcm_oss_look_for_setup(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					   task_name, &setup[0]);
	if (file->f_mode & FMODE_READ)
		snd_pcm_oss_look_for_setup(pcm, SNDRV_PCM_STREAM_CAPTURE,
					   task_name, &setup[1]);

	nonblock = !!(file->f_flags & O_NONBLOCK);
	if (!nonblock)
		nonblock = nonblock_open;

	init_waitqueue_entry(&wait, current);
	add_wait_queue(&pcm->open_wait, &wait);
	mutex_lock(&pcm->open_mutex);
	while (1) {
		err = snd_pcm_oss_open_file(file, pcm, &pcm_oss_file,
					    iminor(inode), setup);
		if (err >= 0)
			break;
		if (err == -EAGAIN) {
			if (nonblock) {
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