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
struct msm_audio_stats {int channel_count; int buffer_count; int /*<<< orphan*/ * unused; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  byte_count; } ;
struct msm_audio_config {int channel_count; int buffer_count; int /*<<< orphan*/ * unused; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  byte_count; } ;
struct file {struct audio* private_data; } ;
struct audio {unsigned long volume; int stopped; int out_channel_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  out_sample_rate; int /*<<< orphan*/  write_lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  dsp_lock; scalar_t__ running; int /*<<< orphan*/  out_bytes; } ;
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
#define  AUDIO_FLUSH 132 
#define  AUDIO_GET_CONFIG 131 
 unsigned int AUDIO_GET_STATS ; 
#define  AUDIO_SET_CONFIG 130 
 unsigned int AUDIO_SET_VOLUME ; 
#define  AUDIO_START 129 
#define  AUDIO_STOP 128 
 int AUDPP_CMD_PCM_INTF_MONO_V ; 
 int AUDPP_CMD_PCM_INTF_STEREO_V ; 
 int /*<<< orphan*/  BUFSZ ; 
 long EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  EV_IOCTL ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int audio_disable (struct audio*) ; 
 int audio_enable (struct audio*) ; 
 int /*<<< orphan*/  audio_flush (struct audio*) ; 
 int /*<<< orphan*/  audpp_set_volume_and_pan (int,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (struct msm_audio_stats*,void*,int) ; 
 scalar_t__ copy_to_user (void*,struct msm_audio_stats*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long audio_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct audio *audio = file->private_data;
	int rc;

	if (cmd == AUDIO_GET_STATS) {
		struct msm_audio_stats stats;
		stats.byte_count = atomic_read(&audio->out_bytes);
		if (copy_to_user((void*) arg, &stats, sizeof(stats)))
			return -EFAULT;
		return 0;
	}
	if (cmd == AUDIO_SET_VOLUME) {
		unsigned long flags;
		spin_lock_irqsave(&audio->dsp_lock, flags);
		audio->volume = arg;
		if (audio->running)
			audpp_set_volume_and_pan(6, arg, 0);
		spin_unlock_irqrestore(&audio->dsp_lock, flags);
	}

	LOG(EV_IOCTL, cmd);
	mutex_lock(&audio->lock);
	switch (cmd) {
	case AUDIO_START:
		rc = audio_enable(audio);
		break;
	case AUDIO_STOP:
		rc = audio_disable(audio);
		audio->stopped = 1;
		break;
	case AUDIO_FLUSH:
		if (audio->stopped) {
			/* Make sure we're stopped and we wake any threads
			 * that might be blocked holding the write_lock.
			 * While audio->stopped write threads will always
			 * exit immediately.
			 */
			wake_up(&audio->wait);
			mutex_lock(&audio->write_lock);
			audio_flush(audio);
			mutex_unlock(&audio->write_lock);
		}
	case AUDIO_SET_CONFIG: {
		struct msm_audio_config config;
		if (copy_from_user(&config, (void*) arg, sizeof(config))) {
			rc = -EFAULT;
			break;
		}
		if (config.channel_count == 1) {
			config.channel_count = AUDPP_CMD_PCM_INTF_MONO_V;
		} else if (config.channel_count == 2) {
			config.channel_count= AUDPP_CMD_PCM_INTF_STEREO_V;
		} else {
			rc = -EINVAL;
			break;
		}
		audio->out_sample_rate = config.sample_rate;
		audio->out_channel_mode = config.channel_count;
		rc = 0;
		break;
	}
	case AUDIO_GET_CONFIG: {
		struct msm_audio_config config;
		config.buffer_size = BUFSZ;
		config.buffer_count = 2;
		config.sample_rate = audio->out_sample_rate;
		if (audio->out_channel_mode == AUDPP_CMD_PCM_INTF_MONO_V) {
			config.channel_count = 1;
		} else {
			config.channel_count = 2;
		}
		config.unused[0] = 0;
		config.unused[1] = 0;
		config.unused[2] = 0;
		config.unused[3] = 0;
		if (copy_to_user((void*) arg, &config, sizeof(config))) {
			rc = -EFAULT;
		} else {
			rc = 0;
		}
		break;
	}
	default:
		rc = -EINVAL;
	}
	mutex_unlock(&audio->lock);
	return rc;
}