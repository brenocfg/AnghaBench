#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int sw_framerate; int sw_channels; int swstate; int sw_fragshift; int sw_subdivshift; int sw_fragcount; int sw_samplefmt; int MSC_offset; int frame_size; int byte_count; int swb_i_avail; int hwbuf_size; int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  chan; int /*<<< orphan*/  hwstate; int /*<<< orphan*/  frag_count; int /*<<< orphan*/  swbuf; } ;
typedef  TYPE_1__ vwsnd_port_t ;
typedef  int /*<<< orphan*/  vwsnd_port_hwstate_t ;
typedef  int vwsnd_port_flags_t ;
struct TYPE_16__ {TYPE_1__ wport; TYPE_1__ rport; } ;
typedef  TYPE_2__ vwsnd_dev_t ;
struct TYPE_17__ {int msc; } ;
typedef  TYPE_3__ ustmsc_t ;
struct inode {int dummy; } ;
struct file {int f_mode; int /*<<< orphan*/  f_lock; int /*<<< orphan*/  f_flags; scalar_t__ private_data; } ;
struct count_info {int fragments; int fragstotal; int fragsize; int bytes; int /*<<< orphan*/  ptr; int /*<<< orphan*/  blocks; } ;
struct audio_buf_info {int fragments; int fragstotal; int fragsize; int bytes; int /*<<< orphan*/  ptr; int /*<<< orphan*/  blocks; } ;

/* Variables and functions */
#define  AFMT_A_LAW 156 
#define  AFMT_MU_LAW 155 
 int AFMT_QUERY ; 
#define  AFMT_S16_LE 154 
#define  AFMT_S8 153 
#define  AFMT_U8 152 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DBGEV (char*,struct inode*,struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  DBGP (char*,unsigned int) ; 
 int /*<<< orphan*/  DBGPV (char*,...) ; 
 int /*<<< orphan*/  DBGX (char*,...) ; 
 int /*<<< orphan*/  DBGXV (char*,...) ; 
 int DISABLED ; 
 int DSP_CAP_DUPLEX ; 
 int DSP_CAP_REALTIME ; 
 int DSP_CAP_TRIGGER ; 
 int EFAULT ; 
 int EINVAL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  HW_RUNNING ; 
 int MAX_FRAGCOUNT (int) ; 
 int MAX_FRAGSHIFT ; 
 int MAX_SPEED ; 
 int MIN_FRAGCOUNT (int) ; 
 int MIN_FRAGSHIFT ; 
 int MIN_SPEED ; 
#define  OSS_GETVERSION 151 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int PCM_ENABLE_INPUT ; 
 int PCM_ENABLE_OUTPUT ; 
#define  SNDCTL_DSP_CHANNELS 150 
#define  SNDCTL_DSP_GETBLKSIZE 149 
#define  SNDCTL_DSP_GETCAPS 148 
#define  SNDCTL_DSP_GETFMTS 147 
#define  SNDCTL_DSP_GETIPTR 146 
#define  SNDCTL_DSP_GETISPACE 145 
#define  SNDCTL_DSP_GETODELAY 144 
#define  SNDCTL_DSP_GETOPTR 143 
#define  SNDCTL_DSP_GETOSPACE 142 
#define  SNDCTL_DSP_GETTRIGGER 141 
#define  SNDCTL_DSP_NONBLOCK 140 
#define  SNDCTL_DSP_POST 139 
#define  SNDCTL_DSP_PROFILE 138 
#define  SNDCTL_DSP_RESET 137 
#define  SNDCTL_DSP_SETFMT 136 
#define  SNDCTL_DSP_SETFRAGMENT 135 
#define  SNDCTL_DSP_SETTRIGGER 134 
#define  SNDCTL_DSP_SPEED 133 
#define  SNDCTL_DSP_STEREO 132 
#define  SNDCTL_DSP_SUBDIVIDE 131 
#define  SNDCTL_DSP_SYNC 130 
#define  SOUND_PCM_READ_CHANNELS 129 
#define  SOUND_PCM_READ_RATE 128 
 int SOUND_VERSION ; 
 int SW_INITIAL ; 
 int SW_RUN ; 
 int /*<<< orphan*/  copy_to_user (void*,struct count_info*,int) ; 
 int /*<<< orphan*/  get_user (int,int*) ; 
 int /*<<< orphan*/  li_activate_dma (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  li_read_USTMSC (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int li_read_swptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcm_flush_frag (TYPE_2__*) ; 
 int /*<<< orphan*/  pcm_output (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcm_setup (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pcm_shutdown (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pcm_write_sync (TYPE_2__*) ; 
 int put_user (int,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int swb_inc_u (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vwsnd_audio_do_ioctl(struct inode *inode,
				struct file *file,
				unsigned int cmd,
				unsigned long arg)
{
	vwsnd_dev_t *devc = (vwsnd_dev_t *) file->private_data;
	vwsnd_port_t *rport = (file->f_mode & FMODE_READ) ?
		&devc->rport : NULL;
	vwsnd_port_t *wport = (file->f_mode & FMODE_WRITE) ?
		&devc->wport : NULL;
	vwsnd_port_t *aport = rport ? rport : wport;
	struct audio_buf_info buf_info;
	struct count_info info;
	unsigned long flags;
	int ival;

	
	DBGEV("(inode=0x%p, file=0x%p, cmd=0x%x, arg=0x%lx)\n",
	      inode, file, cmd, arg);
	switch (cmd) {
	case OSS_GETVERSION:		/* _SIOR ('M', 118, int) */
		DBGX("OSS_GETVERSION\n");
		ival = SOUND_VERSION;
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_GETCAPS:	/* _SIOR ('P',15, int) */
		DBGX("SNDCTL_DSP_GETCAPS\n");
		ival = DSP_CAP_DUPLEX | DSP_CAP_REALTIME | DSP_CAP_TRIGGER;
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_GETFMTS:	/* _SIOR ('P',11, int) */
		DBGX("SNDCTL_DSP_GETFMTS\n");
		ival = (AFMT_S16_LE | AFMT_MU_LAW | AFMT_A_LAW |
			AFMT_U8 | AFMT_S8);
		return put_user(ival, (int *) arg);
		break;

	case SOUND_PCM_READ_RATE:	/* _SIOR ('P', 2, int) */
		DBGX("SOUND_PCM_READ_RATE\n");
		ival = aport->sw_framerate;
		return put_user(ival, (int *) arg);

	case SOUND_PCM_READ_CHANNELS:	/* _SIOR ('P', 6, int) */
		DBGX("SOUND_PCM_READ_CHANNELS\n");
		ival = aport->sw_channels;
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_SPEED:		/* _SIOWR('P', 2, int) */
		if (get_user(ival, (int *) arg))
			return -EFAULT;
		DBGX("SNDCTL_DSP_SPEED %d\n", ival);
		if (ival) {
			if (aport->swstate != SW_INITIAL) {
				DBGX("SNDCTL_DSP_SPEED failed: swstate = %d\n",
				     aport->swstate);
				return -EINVAL;
			}
			if (ival < MIN_SPEED)
				ival = MIN_SPEED;
			if (ival > MAX_SPEED)
				ival = MAX_SPEED;
			if (rport)
				rport->sw_framerate = ival;
			if (wport)
				wport->sw_framerate = ival;
		} else
			ival = aport->sw_framerate;
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_STEREO:		/* _SIOWR('P', 3, int) */
		if (get_user(ival, (int *) arg))
			return -EFAULT;
		DBGX("SNDCTL_DSP_STEREO %d\n", ival);
		if (ival != 0 && ival != 1)
			return -EINVAL;
		if (aport->swstate != SW_INITIAL)
			return -EINVAL;
		if (rport)
			rport->sw_channels = ival + 1;
		if (wport)
			wport->sw_channels = ival + 1;
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_CHANNELS:	/* _SIOWR('P', 6, int) */
		if (get_user(ival, (int *) arg))
			return -EFAULT;
		DBGX("SNDCTL_DSP_CHANNELS %d\n", ival);
		if (ival != 1 && ival != 2)
			return -EINVAL;
		if (aport->swstate != SW_INITIAL)
			return -EINVAL;
		if (rport)
			rport->sw_channels = ival;
		if (wport)
			wport->sw_channels = ival;
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_GETBLKSIZE:	/* _SIOWR('P', 4, int) */
		ival = pcm_setup(devc, rport, wport);
		if (ival < 0) {
			DBGX("SNDCTL_DSP_GETBLKSIZE failed, errno %d\n", ival);
			return ival;
		}
		ival = 1 << aport->sw_fragshift;
		DBGX("SNDCTL_DSP_GETBLKSIZE returning %d\n", ival);
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_SETFRAGMENT:	/* _SIOWR('P',10, int) */
		if (get_user(ival, (int *) arg))
			return -EFAULT;
		DBGX("SNDCTL_DSP_SETFRAGMENT %d:%d\n",
		     ival >> 16, ival & 0xFFFF);
		if (aport->swstate != SW_INITIAL)
			return -EINVAL;
		{
			int sw_fragshift = ival & 0xFFFF;
			int sw_subdivshift = aport->sw_subdivshift;
			int hw_fragshift = sw_fragshift - sw_subdivshift;
			int sw_fragcount = (ival >> 16) & 0xFFFF;
			int hw_fragsize;
			if (hw_fragshift < MIN_FRAGSHIFT)
				hw_fragshift = MIN_FRAGSHIFT;
			if (hw_fragshift > MAX_FRAGSHIFT)
				hw_fragshift = MAX_FRAGSHIFT;
			sw_fragshift = hw_fragshift + aport->sw_subdivshift;
			hw_fragsize = 1 << hw_fragshift;
			if (sw_fragcount < MIN_FRAGCOUNT(hw_fragsize))
				sw_fragcount = MIN_FRAGCOUNT(hw_fragsize);
			if (sw_fragcount > MAX_FRAGCOUNT(hw_fragsize))
				sw_fragcount = MAX_FRAGCOUNT(hw_fragsize);
			DBGPV("sw_fragshift = %d\n", sw_fragshift);
			DBGPV("rport = 0x%p, wport = 0x%p\n", rport, wport);
			if (rport) {
				rport->sw_fragshift = sw_fragshift;
				rport->sw_fragcount = sw_fragcount;
			}
			if (wport) {
				wport->sw_fragshift = sw_fragshift;
				wport->sw_fragcount = sw_fragcount;
			}
			ival = sw_fragcount << 16 | sw_fragshift;
		}
		DBGX("SNDCTL_DSP_SETFRAGMENT returns %d:%d\n",
		      ival >> 16, ival & 0xFFFF);
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_SUBDIVIDE:	/* _SIOWR('P', 9, int) */
                if (get_user(ival, (int *) arg))
			return -EFAULT;
		DBGX("SNDCTL_DSP_SUBDIVIDE %d\n", ival);
		if (aport->swstate != SW_INITIAL)
			return -EINVAL;
		{
			int subdivshift;
			int hw_fragshift, hw_fragsize, hw_fragcount;
			switch (ival) {
			case 1: subdivshift = 0; break;
			case 2: subdivshift = 1; break;
			case 4: subdivshift = 2; break;
			default: return -EINVAL;
			}
			hw_fragshift = aport->sw_fragshift - subdivshift;
			if (hw_fragshift < MIN_FRAGSHIFT ||
			    hw_fragshift > MAX_FRAGSHIFT)
				return -EINVAL;
			hw_fragsize = 1 << hw_fragshift;
			hw_fragcount = aport->sw_fragcount >> subdivshift;
			if (hw_fragcount < MIN_FRAGCOUNT(hw_fragsize) ||
			    hw_fragcount > MAX_FRAGCOUNT(hw_fragsize))
				return -EINVAL;
			if (rport)
				rport->sw_subdivshift = subdivshift;
			if (wport)
				wport->sw_subdivshift = subdivshift;
		}
		return 0;

	case SNDCTL_DSP_SETFMT:		/* _SIOWR('P',5, int) */
		if (get_user(ival, (int *) arg))
			return -EFAULT;
		DBGX("SNDCTL_DSP_SETFMT %d\n", ival);
		if (ival != AFMT_QUERY) {
			if (aport->swstate != SW_INITIAL) {
				DBGP("SETFMT failed, swstate = %d\n",
				     aport->swstate);
				return -EINVAL;
			}
			switch (ival) {
			case AFMT_MU_LAW:
			case AFMT_A_LAW:
			case AFMT_U8:
			case AFMT_S8:
			case AFMT_S16_LE:
				if (rport)
					rport->sw_samplefmt = ival;
				if (wport)
					wport->sw_samplefmt = ival;
				break;
			default:
				return -EINVAL;
			}
		}
		ival = aport->sw_samplefmt;
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_GETOSPACE:	/* _SIOR ('P',12, audio_buf_info) */
		DBGXV("SNDCTL_DSP_GETOSPACE\n");
		if (!wport)
			return -EINVAL;
		ival = pcm_setup(devc, rport, wport);
		if (ival < 0)
			return ival;
		ival = swb_inc_u(wport, 0);
		buf_info.fragments = ival >> wport->sw_fragshift;
		buf_info.fragstotal = wport->sw_fragcount;
		buf_info.fragsize = 1 << wport->sw_fragshift;
		buf_info.bytes = ival;
		DBGXV("SNDCTL_DSP_GETOSPACE returns { %d %d %d %d }\n",
		     buf_info.fragments, buf_info.fragstotal,
		     buf_info.fragsize, buf_info.bytes);
		if (copy_to_user((void *) arg, &buf_info, sizeof buf_info))
			return -EFAULT;
		return 0;

	case SNDCTL_DSP_GETISPACE:	/* _SIOR ('P',13, audio_buf_info) */
		DBGX("SNDCTL_DSP_GETISPACE\n");
		if (!rport)
			return -EINVAL;
		ival = pcm_setup(devc, rport, wport);
		if (ival < 0)
			return ival;
		ival = swb_inc_u(rport, 0);
		buf_info.fragments = ival >> rport->sw_fragshift;
		buf_info.fragstotal = rport->sw_fragcount;
		buf_info.fragsize = 1 << rport->sw_fragshift;
		buf_info.bytes = ival;
		DBGX("SNDCTL_DSP_GETISPACE returns { %d %d %d %d }\n",
		     buf_info.fragments, buf_info.fragstotal,
		     buf_info.fragsize, buf_info.bytes);
		if (copy_to_user((void *) arg, &buf_info, sizeof buf_info))
			return -EFAULT;
		return 0;

	case SNDCTL_DSP_NONBLOCK:	/* _SIO  ('P',14) */
		DBGX("SNDCTL_DSP_NONBLOCK\n");
		spin_lock(&file->f_lock);
		file->f_flags |= O_NONBLOCK;
		spin_unlock(&file->f_lock);
		return 0;

	case SNDCTL_DSP_RESET:		/* _SIO  ('P', 0) */
		DBGX("SNDCTL_DSP_RESET\n");
		/*
		 * Nothing special needs to be done for input.  Input
		 * samples sit in swbuf, but it will be reinitialized
		 * to empty when pcm_setup() is called.
		 */
		if (wport && wport->swbuf) {
			wport->swstate = SW_INITIAL;
			pcm_output(devc, 0, 0);
			pcm_write_sync(devc);
		}
		pcm_shutdown(devc, rport, wport);
		return 0;

	case SNDCTL_DSP_SYNC:		/* _SIO  ('P', 1) */
		DBGX("SNDCTL_DSP_SYNC\n");
		if (wport) {
			pcm_flush_frag(devc);
			pcm_write_sync(devc);
		}
		pcm_shutdown(devc, rport, wport);
		return 0;

	case SNDCTL_DSP_POST:		/* _SIO  ('P', 8) */
		DBGX("SNDCTL_DSP_POST\n");
		if (!wport)
			return -EINVAL;
		pcm_flush_frag(devc);
		return 0;

	case SNDCTL_DSP_GETIPTR:	/* _SIOR ('P', 17, count_info) */
		DBGX("SNDCTL_DSP_GETIPTR\n");
		if (!rport)
			return -EINVAL;
		spin_lock_irqsave(&rport->lock, flags);
		{
			ustmsc_t ustmsc;
			if (rport->hwstate == HW_RUNNING) {
				ASSERT(rport->swstate == SW_RUN);
				li_read_USTMSC(&rport->chan, &ustmsc);
				info.bytes = ustmsc.msc - rport->MSC_offset;
				info.bytes *= rport->frame_size;
			} else {
				info.bytes = rport->byte_count;
			}
			info.blocks = rport->frag_count;
			info.ptr = 0;	/* not implemented */
			rport->frag_count = 0;
		}
		spin_unlock_irqrestore(&rport->lock, flags);
		if (copy_to_user((void *) arg, &info, sizeof info))
			return -EFAULT;
		return 0;

	case SNDCTL_DSP_GETOPTR:	/* _SIOR ('P',18, count_info) */
		DBGX("SNDCTL_DSP_GETOPTR\n");
		if (!wport)
			return -EINVAL;
		spin_lock_irqsave(&wport->lock, flags);
		{
			ustmsc_t ustmsc;
			if (wport->hwstate == HW_RUNNING) {
				ASSERT(wport->swstate == SW_RUN);
				li_read_USTMSC(&wport->chan, &ustmsc);
				info.bytes = ustmsc.msc - wport->MSC_offset;
				info.bytes *= wport->frame_size;
			} else {
				info.bytes = wport->byte_count;
			}
			info.blocks = wport->frag_count;
			info.ptr = 0;	/* not implemented */
			wport->frag_count = 0;
		}
		spin_unlock_irqrestore(&wport->lock, flags);
		if (copy_to_user((void *) arg, &info, sizeof info))
			return -EFAULT;
		return 0;

	case SNDCTL_DSP_GETODELAY:	/* _SIOR ('P', 23, int) */
		DBGX("SNDCTL_DSP_GETODELAY\n");
		if (!wport)
			return -EINVAL;
		spin_lock_irqsave(&wport->lock, flags);
		{
			int fsize = wport->frame_size;
			ival = wport->swb_i_avail / fsize;
			if (wport->hwstate == HW_RUNNING) {
				int swptr, hwptr, hwframes, hwbytes, hwsize;
				int totalhwbytes;
				ustmsc_t ustmsc;

				hwsize = wport->hwbuf_size;
				swptr = li_read_swptr(&wport->chan);
				li_read_USTMSC(&wport->chan, &ustmsc);
				hwframes = ustmsc.msc - wport->MSC_offset;
				totalhwbytes = hwframes * fsize;
				hwptr = totalhwbytes % hwsize;
				hwbytes = (swptr - hwptr + hwsize) % hwsize;
				ival += hwbytes / fsize;
			}
		}
		spin_unlock_irqrestore(&wport->lock, flags);
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_PROFILE:	/* _SIOW ('P', 23, int) */
		DBGX("SNDCTL_DSP_PROFILE\n");

		/*
		 * Thomas Sailer explains SNDCTL_DSP_PROFILE
		 * (private email, March 24, 1999):
		 *
		 *     This gives the sound driver a hint on what it
		 *     should do with partial fragments
		 *     (i.e. fragments partially filled with write).
		 *     This can direct the driver to zero them or
		 *     leave them alone.  But don't ask me what this
		 *     is good for, my driver just zeroes the last
		 *     fragment before the receiver stops, no idea
		 *     what good for any other behaviour could
		 *     be. Implementing it as NOP seems safe.
		 */

		break;

	case SNDCTL_DSP_GETTRIGGER:	/* _SIOR ('P',16, int) */
		DBGX("SNDCTL_DSP_GETTRIGGER\n");
		ival = 0;
		if (rport) {
			spin_lock_irqsave(&rport->lock, flags);
			{
				if (!(rport->flags & DISABLED))
					ival |= PCM_ENABLE_INPUT;
			}
			spin_unlock_irqrestore(&rport->lock, flags);
		}
		if (wport) {
			spin_lock_irqsave(&wport->lock, flags);
			{
				if (!(wport->flags & DISABLED))
					ival |= PCM_ENABLE_OUTPUT;
			}
			spin_unlock_irqrestore(&wport->lock, flags);
		}
		return put_user(ival, (int *) arg);

	case SNDCTL_DSP_SETTRIGGER:	/* _SIOW ('P',16, int) */
		if (get_user(ival, (int *) arg))
			return -EFAULT;
		DBGX("SNDCTL_DSP_SETTRIGGER %d\n", ival);

		/*
		 * If user is disabling I/O and port is not in initial
		 * state, fail with EINVAL.
		 */

		if (((rport && !(ival & PCM_ENABLE_INPUT)) ||
		     (wport && !(ival & PCM_ENABLE_OUTPUT))) &&
		    aport->swstate != SW_INITIAL)
			return -EINVAL;

		if (rport) {
			vwsnd_port_hwstate_t hwstate;
			spin_lock_irqsave(&rport->lock, flags);
			{
				hwstate = rport->hwstate;
				if (ival & PCM_ENABLE_INPUT)
					rport->flags &= ~DISABLED;
				else
					rport->flags |= DISABLED;
			}
			spin_unlock_irqrestore(&rport->lock, flags);
			if (hwstate != HW_RUNNING && ival & PCM_ENABLE_INPUT) {

				if (rport->swstate == SW_INITIAL)
					pcm_setup(devc, rport, wport);
				else
					li_activate_dma(&rport->chan);
			}
		}
		if (wport) {
			vwsnd_port_flags_t pflags;
			spin_lock_irqsave(&wport->lock, flags);
			{
				pflags = wport->flags;
				if (ival & PCM_ENABLE_OUTPUT)
					wport->flags &= ~DISABLED;
				else
					wport->flags |= DISABLED;
			}
			spin_unlock_irqrestore(&wport->lock, flags);
			if (pflags & DISABLED && ival & PCM_ENABLE_OUTPUT) {
				if (wport->swstate == SW_RUN)
					pcm_output(devc, 0, 0);
			}
		}
		return 0;

	default:
		DBGP("unknown ioctl 0x%x\n", cmd);
		return -EINVAL;
	}
	DBGP("unimplemented ioctl 0x%x\n", cmd);
	return -EINVAL;
}