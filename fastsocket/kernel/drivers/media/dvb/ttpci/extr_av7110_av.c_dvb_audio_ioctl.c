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
struct file {int f_flags; struct dvb_device* private_data; } ;
struct dvb_device {struct av7110* priv; } ;
struct TYPE_2__ {int mute_state; int AV_sync_state; int bypass_mode; int /*<<< orphan*/  channel_select; int /*<<< orphan*/  stream_source; void* play_state; } ;
struct av7110 {int /*<<< orphan*/  playing; int /*<<< orphan*/ * ipack; int /*<<< orphan*/  aout; int /*<<< orphan*/  arm_app; TYPE_1__ audiostate; int /*<<< orphan*/  adac_type; } ;
struct audio_status {int dummy; } ;
struct audio_mixer {int /*<<< orphan*/  volume_right; int /*<<< orphan*/  volume_left; } ;
typedef  int /*<<< orphan*/  audio_stream_source_t ;
typedef  int /*<<< orphan*/  audio_channel_select_t ;

/* Variables and functions */
 unsigned int AUDIO_CAP_AC3 ; 
 unsigned int AUDIO_CAP_DTS ; 
 unsigned int AUDIO_CAP_LPCM ; 
 unsigned int AUDIO_CAP_MP1 ; 
 unsigned int AUDIO_CAP_MP2 ; 
#define  AUDIO_CHANNEL_SELECT 145 
#define  AUDIO_CLEAR_BUFFER 144 
 int AUDIO_CMD_MONO_L ; 
 int AUDIO_CMD_MONO_R ; 
 int AUDIO_CMD_MUTE ; 
 int AUDIO_CMD_PCM16 ; 
 int AUDIO_CMD_STEREO ; 
 int AUDIO_CMD_SYNC_OFF ; 
 int AUDIO_CMD_SYNC_ON ; 
 int AUDIO_CMD_UNMUTE ; 
#define  AUDIO_CONTINUE 143 
#define  AUDIO_GET_CAPABILITIES 142 
#define  AUDIO_GET_STATUS 141 
#define  AUDIO_MONO_LEFT 140 
#define  AUDIO_MONO_RIGHT 139 
#define  AUDIO_PAUSE 138 
 void* AUDIO_PAUSED ; 
#define  AUDIO_PLAY 137 
 void* AUDIO_PLAYING ; 
#define  AUDIO_SELECT_SOURCE 136 
#define  AUDIO_SET_AV_SYNC 135 
#define  AUDIO_SET_BYPASS_MODE 134 
#define  AUDIO_SET_ID 133 
#define  AUDIO_SET_MIXER 132 
#define  AUDIO_SET_MUTE 131 
#define  AUDIO_SET_STREAMTYPE 130 
 int /*<<< orphan*/  AUDIO_SOURCE_MEMORY ; 
#define  AUDIO_STEREO 129 
#define  AUDIO_STOP 128 
 void* AUDIO_STOPPED ; 
 int /*<<< orphan*/  AV_PES ; 
 int /*<<< orphan*/  COMTYPE_REC_PLAY ; 
 int /*<<< orphan*/  DVB_ADAC_CRYSTAL ; 
 int /*<<< orphan*/  DVB_ADAC_MSP34x5 ; 
 int EINVAL ; 
 int ENOIOCTLCMD ; 
 int EPERM ; 
 int FW_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSP_WR_DSP ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  RP_AUDIO ; 
 int /*<<< orphan*/  RP_AV ; 
 int /*<<< orphan*/  __Play ; 
 int audcom (struct av7110*,int) ; 
 int av7110_av_start_play (struct av7110*,int /*<<< orphan*/ ) ; 
 int av7110_av_stop (struct av7110*,int /*<<< orphan*/ ) ; 
 int av7110_fw_cmd (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av7110_ipack_reset (int /*<<< orphan*/ *) ; 
 int av7110_set_volume (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*,unsigned int) ; 
 int /*<<< orphan*/  dvb_ringbuffer_flush_spinlock_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_writereg (struct av7110*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (void*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  msp_writereg (struct av7110*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int dvb_audio_ioctl(struct inode *inode, struct file *file,
			   unsigned int cmd, void *parg)
{
	struct dvb_device *dvbdev = file->private_data;
	struct av7110 *av7110 = dvbdev->priv;
	unsigned long arg = (unsigned long) parg;
	int ret = 0;

	dprintk(1, "av7110:%p, cmd=%04x\n", av7110,cmd);

	if (((file->f_flags & O_ACCMODE) == O_RDONLY) &&
	    (cmd != AUDIO_GET_STATUS))
		return -EPERM;

	switch (cmd) {
	case AUDIO_STOP:
		if (av7110->audiostate.stream_source == AUDIO_SOURCE_MEMORY)
			ret = av7110_av_stop(av7110, RP_AUDIO);
		else
			ret = audcom(av7110, AUDIO_CMD_MUTE);
		if (!ret)
			av7110->audiostate.play_state = AUDIO_STOPPED;
		break;

	case AUDIO_PLAY:
		if (av7110->audiostate.stream_source == AUDIO_SOURCE_MEMORY)
			ret = av7110_av_start_play(av7110, RP_AUDIO);
		if (!ret)
			ret = audcom(av7110, AUDIO_CMD_UNMUTE);
		if (!ret)
			av7110->audiostate.play_state = AUDIO_PLAYING;
		break;

	case AUDIO_PAUSE:
		ret = audcom(av7110, AUDIO_CMD_MUTE);
		if (!ret)
			av7110->audiostate.play_state = AUDIO_PAUSED;
		break;

	case AUDIO_CONTINUE:
		if (av7110->audiostate.play_state == AUDIO_PAUSED) {
			av7110->audiostate.play_state = AUDIO_PLAYING;
			ret = audcom(av7110, AUDIO_CMD_UNMUTE | AUDIO_CMD_PCM16);
		}
		break;

	case AUDIO_SELECT_SOURCE:
		av7110->audiostate.stream_source = (audio_stream_source_t) arg;
		break;

	case AUDIO_SET_MUTE:
	{
		ret = audcom(av7110, arg ? AUDIO_CMD_MUTE : AUDIO_CMD_UNMUTE);
		if (!ret)
			av7110->audiostate.mute_state = (int) arg;
		break;
	}

	case AUDIO_SET_AV_SYNC:
		av7110->audiostate.AV_sync_state = (int) arg;
		ret = audcom(av7110, arg ? AUDIO_CMD_SYNC_ON : AUDIO_CMD_SYNC_OFF);
		break;

	case AUDIO_SET_BYPASS_MODE:
		if (FW_VERSION(av7110->arm_app) < 0x2621)
			ret = -EINVAL;
		av7110->audiostate.bypass_mode = (int)arg;
		break;

	case AUDIO_CHANNEL_SELECT:
		av7110->audiostate.channel_select = (audio_channel_select_t) arg;
		switch(av7110->audiostate.channel_select) {
		case AUDIO_STEREO:
			ret = audcom(av7110, AUDIO_CMD_STEREO);
			if (!ret) {
				if (av7110->adac_type == DVB_ADAC_CRYSTAL)
					i2c_writereg(av7110, 0x20, 0x02, 0x49);
				else if (av7110->adac_type == DVB_ADAC_MSP34x5)
					msp_writereg(av7110, MSP_WR_DSP, 0x0008, 0x0220);
			}
			break;
		case AUDIO_MONO_LEFT:
			ret = audcom(av7110, AUDIO_CMD_MONO_L);
			if (!ret) {
				if (av7110->adac_type == DVB_ADAC_CRYSTAL)
					i2c_writereg(av7110, 0x20, 0x02, 0x4a);
				else if (av7110->adac_type == DVB_ADAC_MSP34x5)
					msp_writereg(av7110, MSP_WR_DSP, 0x0008, 0x0200);
			}
			break;
		case AUDIO_MONO_RIGHT:
			ret = audcom(av7110, AUDIO_CMD_MONO_R);
			if (!ret) {
				if (av7110->adac_type == DVB_ADAC_CRYSTAL)
					i2c_writereg(av7110, 0x20, 0x02, 0x45);
				else if (av7110->adac_type == DVB_ADAC_MSP34x5)
					msp_writereg(av7110, MSP_WR_DSP, 0x0008, 0x0210);
			}
			break;
		default:
			ret = -EINVAL;
			break;
		}
		break;

	case AUDIO_GET_STATUS:
		memcpy(parg, &av7110->audiostate, sizeof(struct audio_status));
		break;

	case AUDIO_GET_CAPABILITIES:
		if (FW_VERSION(av7110->arm_app) < 0x2621)
			*(unsigned int *)parg = AUDIO_CAP_LPCM | AUDIO_CAP_MP1 | AUDIO_CAP_MP2;
		else
			*(unsigned int *)parg = AUDIO_CAP_LPCM | AUDIO_CAP_DTS | AUDIO_CAP_AC3 |
						AUDIO_CAP_MP1 | AUDIO_CAP_MP2;
		break;

	case AUDIO_CLEAR_BUFFER:
		dvb_ringbuffer_flush_spinlock_wakeup(&av7110->aout);
		av7110_ipack_reset(&av7110->ipack[0]);
		if (av7110->playing == RP_AV)
			ret = av7110_fw_cmd(av7110, COMTYPE_REC_PLAY,
					    __Play, 2, AV_PES, 0);
		break;

	case AUDIO_SET_ID:
		break;

	case AUDIO_SET_MIXER:
	{
		struct audio_mixer *amix = (struct audio_mixer *)parg;
		ret = av7110_set_volume(av7110, amix->volume_left, amix->volume_right);
		break;
	}

	case AUDIO_SET_STREAMTYPE:
		break;

	default:
		ret = -ENOIOCTLCMD;
	}

	return ret;
}