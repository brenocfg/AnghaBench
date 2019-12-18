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
struct msm_audio_stats {int channel_count; int type; int /*<<< orphan*/ * unused; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  buffer_count; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  byte_count; } ;
struct msm_audio_config {int channel_count; int type; int /*<<< orphan*/ * unused; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  buffer_count; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  byte_count; } ;
struct file {struct audio_in* private_data; } ;
struct audio_in {int stopped; int channel_mode; int type; int /*<<< orphan*/  lock; int /*<<< orphan*/  samp_rate; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  samp_rate_index; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  in_bytes; } ;
typedef  int /*<<< orphan*/  stats ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
#define  AUDIO_FLUSH 132 
#define  AUDIO_GET_CONFIG 131 
 unsigned int AUDIO_GET_STATS ; 
#define  AUDIO_SET_CONFIG 130 
#define  AUDIO_START 129 
#define  AUDIO_STOP 128 
 int AUDREC_CMD_STEREO_MODE_MONO ; 
 int AUDREC_CMD_STEREO_MODE_STEREO ; 
 int AUDREC_CMD_TYPE_0_INDEX_AAC ; 
 int AUDREC_CMD_TYPE_0_INDEX_WAV ; 
 long EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  FRAME_NUM ; 
 int /*<<< orphan*/  MONO_DATA_SIZE ; 
 int /*<<< orphan*/  STEREO_DATA_SIZE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audio_flush (struct audio_in*) ; 
 int audio_in_disable (struct audio_in*) ; 
 int audio_in_enable (struct audio_in*) ; 
 int /*<<< orphan*/  convert_dsp_samp_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_samp_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_samp_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_from_user (struct msm_audio_stats*,void*,int) ; 
 scalar_t__ copy_to_user (void*,struct msm_audio_stats*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long audio_in_ioctl(struct file *file,
				unsigned int cmd, unsigned long arg)
{
	struct audio_in *audio = file->private_data;
	int rc;

	if (cmd == AUDIO_GET_STATS) {
		struct msm_audio_stats stats;
		stats.byte_count = atomic_read(&audio->in_bytes);
		if (copy_to_user((void *) arg, &stats, sizeof(stats)))
			return -EFAULT;
		return 0;
	}

	mutex_lock(&audio->lock);
	switch (cmd) {
	case AUDIO_START:
		rc = audio_in_enable(audio);
		break;
	case AUDIO_STOP:
		rc = audio_in_disable(audio);
		audio->stopped = 1;
		break;
	case AUDIO_FLUSH:
		if (audio->stopped) {
			/* Make sure we're stopped and we wake any threads
			 * that might be blocked holding the read_lock.
			 * While audio->stopped read threads will always
			 * exit immediately.
			 */
			wake_up(&audio->wait);
			mutex_lock(&audio->read_lock);
			audio_flush(audio);
			mutex_unlock(&audio->read_lock);
		}
	case AUDIO_SET_CONFIG: {
		struct msm_audio_config cfg;
		if (copy_from_user(&cfg, (void *) arg, sizeof(cfg))) {
			rc = -EFAULT;
			break;
		}
		if (cfg.channel_count == 1) {
			cfg.channel_count = AUDREC_CMD_STEREO_MODE_MONO;
		} else if (cfg.channel_count == 2) {
			cfg.channel_count = AUDREC_CMD_STEREO_MODE_STEREO;
		} else {
			rc = -EINVAL;
			break;
		}

		if (cfg.type == 0) {
			cfg.type = AUDREC_CMD_TYPE_0_INDEX_WAV;
		} else if (cfg.type == 1) {
			cfg.type = AUDREC_CMD_TYPE_0_INDEX_AAC;
		} else {
			rc = -EINVAL;
			break;
		}
		audio->samp_rate = convert_samp_rate(cfg.sample_rate);
		audio->samp_rate_index =
		  convert_dsp_samp_index(cfg.sample_rate);
		audio->channel_mode = cfg.channel_count;
		audio->buffer_size =
				audio->channel_mode ? STEREO_DATA_SIZE
							: MONO_DATA_SIZE;
		audio->type = cfg.type;
		rc = 0;
		break;
	}
	case AUDIO_GET_CONFIG: {
		struct msm_audio_config cfg;
		cfg.buffer_size = audio->buffer_size;
		cfg.buffer_count = FRAME_NUM;
		cfg.sample_rate = convert_samp_index(audio->samp_rate);
		if (audio->channel_mode == AUDREC_CMD_STEREO_MODE_MONO)
			cfg.channel_count = 1;
		else
			cfg.channel_count = 2;
		if (audio->type == AUDREC_CMD_TYPE_0_INDEX_WAV)
			cfg.type = 0;
		else
			cfg.type = 1;
		cfg.unused[0] = 0;
		cfg.unused[1] = 0;
		cfg.unused[2] = 0;
		if (copy_to_user((void *) arg, &cfg, sizeof(cfg)))
			rc = -EFAULT;
		else
			rc = 0;
		break;
	}
	default:
		rc = -EINVAL;
	}
	mutex_unlock(&audio->lock);
	return rc;
}