#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct inode {int dummy; } ;
struct file {int f_mode; int f_flags; int /*<<< orphan*/  f_lock; scalar_t__ private_data; } ;
struct TYPE_9__ {int mapped; int count; int total_bytes; int sample_rate; int num_channels; int sample_size; int fragsize; int cnt_factor; int fragshift; int ossfragshift; int ossmaxfrags; int subdivision; int /*<<< orphan*/  dma_fragsize; int /*<<< orphan*/  rawbuf; int /*<<< orphan*/  nextOut; int /*<<< orphan*/  stopped; int /*<<< orphan*/  nextIn; int /*<<< orphan*/  numfrag; int /*<<< orphan*/  dmasize; } ;
struct au1550_state {int open_mode; int codec_ext_caps; int /*<<< orphan*/  codec; TYPE_4__ dma_dac; TYPE_4__ dma_adc; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int fragsize; int bytes; int fragments; int blocks; void* ptr; int /*<<< orphan*/  fragstotal; } ;
typedef  TYPE_1__ count_info ;
typedef  int /*<<< orphan*/  cinfo ;
typedef  TYPE_1__ audio_buf_info ;
typedef  int /*<<< orphan*/  abinfo ;
struct TYPE_8__ {unsigned int cmd; unsigned int str; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_STATUS ; 
 int AC97_EXTID_SDAC ; 
 int AC97_EXTSTAT_PRI ; 
 int AC97_EXTSTAT_PRJ ; 
 int AC97_EXTSTAT_PRK ; 
 int AC97_EXT_DACS ; 
 int AFMT_QUERY ; 
 int AFMT_S16_LE ; 
 int AFMT_U8 ; 
 int ARRAY_SIZE (TYPE_3__*) ; 
 int DSP_CAP_DUPLEX ; 
 int DSP_CAP_MMAP ; 
 int DSP_CAP_REALTIME ; 
 int DSP_CAP_TRIGGER ; 
 int EFAULT ; 
 int EINVAL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
#define  OSS_GETVERSION 155 
 int O_NONBLOCK ; 
 int PCM_ENABLE_INPUT ; 
 int PCM_ENABLE_OUTPUT ; 
#define  SNDCTL_DSP_CHANNELS 154 
#define  SNDCTL_DSP_GETBLKSIZE 153 
#define  SNDCTL_DSP_GETCAPS 152 
#define  SNDCTL_DSP_GETFMTS 151 
#define  SNDCTL_DSP_GETIPTR 150 
#define  SNDCTL_DSP_GETISPACE 149 
#define  SNDCTL_DSP_GETODELAY 148 
#define  SNDCTL_DSP_GETOPTR 147 
#define  SNDCTL_DSP_GETOSPACE 146 
#define  SNDCTL_DSP_GETTRIGGER 145 
#define  SNDCTL_DSP_NONBLOCK 144 
#define  SNDCTL_DSP_POST 143 
#define  SNDCTL_DSP_RESET 142 
#define  SNDCTL_DSP_SETDUPLEX 141 
#define  SNDCTL_DSP_SETFMT 140 
#define  SNDCTL_DSP_SETFRAGMENT 139 
#define  SNDCTL_DSP_SETSYNCRO 138 
#define  SNDCTL_DSP_SETTRIGGER 137 
#define  SNDCTL_DSP_SPEED 136 
#define  SNDCTL_DSP_STEREO 135 
#define  SNDCTL_DSP_SUBDIVIDE 134 
#define  SNDCTL_DSP_SYNC 133 
#define  SOUND_PCM_READ_BITS 132 
#define  SOUND_PCM_READ_CHANNELS 131 
#define  SOUND_PCM_READ_FILTER 130 
#define  SOUND_PCM_READ_RATE 129 
#define  SOUND_PCM_WRITE_FILTER 128 
 int SOUND_VERSION ; 
 int copy_to_user (void*,TYPE_1__*,int) ; 
 int dma_count_done (TYPE_4__*) ; 
 int drain_dac (struct au1550_state*,int) ; 
 int /*<<< orphan*/  get_user (int,int*) ; 
 TYPE_3__* ioctl_str ; 
 int mixdev_ioctl (int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned long) ; 
 int prog_dmabuf_adc (struct au1550_state*) ; 
 int prog_dmabuf_dac (struct au1550_state*) ; 
 int put_user (int,int*) ; 
 int rdcodec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_adc_rate (struct au1550_state*,int) ; 
 int /*<<< orphan*/  set_dac_rate (struct au1550_state*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_adc (struct au1550_state*) ; 
 int /*<<< orphan*/  start_dac (struct au1550_state*) ; 
 int /*<<< orphan*/  stop_adc (struct au1550_state*) ; 
 int /*<<< orphan*/  stop_dac (struct au1550_state*) ; 
 int /*<<< orphan*/  synchronize_irq () ; 
 void* virt_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrcodec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
au1550_ioctl(struct inode *inode, struct file *file, unsigned int cmd,
							unsigned long arg)
{
	struct au1550_state *s = (struct au1550_state *)file->private_data;
	unsigned long   flags;
	audio_buf_info  abinfo;
	count_info      cinfo;
	int             count;
	int             val, mapped, ret, diff;

	mapped = ((file->f_mode & FMODE_WRITE) && s->dma_dac.mapped) ||
		((file->f_mode & FMODE_READ) && s->dma_adc.mapped);

#ifdef DEBUG
	for (count = 0; count < ARRAY_SIZE(ioctl_str); count++) {
		if (ioctl_str[count].cmd == cmd)
			break;
	}
	if (count < ARRAY_SIZE(ioctl_str))
		pr_debug("ioctl %s, arg=0x%lxn", ioctl_str[count].str, arg);
	else
		pr_debug("ioctl 0x%x unknown, arg=0x%lx\n", cmd, arg);
#endif

	switch (cmd) {
	case OSS_GETVERSION:
		return put_user(SOUND_VERSION, (int *) arg);

	case SNDCTL_DSP_SYNC:
		if (file->f_mode & FMODE_WRITE)
			return drain_dac(s, file->f_flags & O_NONBLOCK);
		return 0;

	case SNDCTL_DSP_SETDUPLEX:
		return 0;

	case SNDCTL_DSP_GETCAPS:
		return put_user(DSP_CAP_DUPLEX | DSP_CAP_REALTIME |
				DSP_CAP_TRIGGER | DSP_CAP_MMAP, (int *)arg);

	case SNDCTL_DSP_RESET:
		if (file->f_mode & FMODE_WRITE) {
			stop_dac(s);
			synchronize_irq();
			s->dma_dac.count = s->dma_dac.total_bytes = 0;
			s->dma_dac.nextIn = s->dma_dac.nextOut =
				s->dma_dac.rawbuf;
		}
		if (file->f_mode & FMODE_READ) {
			stop_adc(s);
			synchronize_irq();
			s->dma_adc.count = s->dma_adc.total_bytes = 0;
			s->dma_adc.nextIn = s->dma_adc.nextOut =
				s->dma_adc.rawbuf;
		}
		return 0;

	case SNDCTL_DSP_SPEED:
		if (get_user(val, (int *) arg))
			return -EFAULT;
		if (val >= 0) {
			if (file->f_mode & FMODE_READ) {
				stop_adc(s);
				set_adc_rate(s, val);
			}
			if (file->f_mode & FMODE_WRITE) {
				stop_dac(s);
				set_dac_rate(s, val);
			}
			if (s->open_mode & FMODE_READ)
				if ((ret = prog_dmabuf_adc(s)))
					return ret;
			if (s->open_mode & FMODE_WRITE)
				if ((ret = prog_dmabuf_dac(s)))
					return ret;
		}
		return put_user((file->f_mode & FMODE_READ) ?
				s->dma_adc.sample_rate :
				s->dma_dac.sample_rate,
				(int *)arg);

	case SNDCTL_DSP_STEREO:
		if (get_user(val, (int *) arg))
			return -EFAULT;
		if (file->f_mode & FMODE_READ) {
			stop_adc(s);
			s->dma_adc.num_channels = val ? 2 : 1;
			if ((ret = prog_dmabuf_adc(s)))
				return ret;
		}
		if (file->f_mode & FMODE_WRITE) {
			stop_dac(s);
			s->dma_dac.num_channels = val ? 2 : 1;
			if (s->codec_ext_caps & AC97_EXT_DACS) {
				/* disable surround and center/lfe in AC'97
				*/
				u16 ext_stat = rdcodec(s->codec,
						       AC97_EXTENDED_STATUS);
				wrcodec(s->codec, AC97_EXTENDED_STATUS,
					ext_stat | (AC97_EXTSTAT_PRI |
						    AC97_EXTSTAT_PRJ |
						    AC97_EXTSTAT_PRK));
			}
			if ((ret = prog_dmabuf_dac(s)))
				return ret;
		}
		return 0;

	case SNDCTL_DSP_CHANNELS:
		if (get_user(val, (int *) arg))
			return -EFAULT;
		if (val != 0) {
			if (file->f_mode & FMODE_READ) {
				if (val < 0 || val > 2)
					return -EINVAL;
				stop_adc(s);
				s->dma_adc.num_channels = val;
				if ((ret = prog_dmabuf_adc(s)))
					return ret;
			}
			if (file->f_mode & FMODE_WRITE) {
				switch (val) {
				case 1:
				case 2:
					break;
				case 3:
				case 5:
					return -EINVAL;
				case 4:
					if (!(s->codec_ext_caps &
					      AC97_EXTID_SDAC))
						return -EINVAL;
					break;
				case 6:
					if ((s->codec_ext_caps &
					     AC97_EXT_DACS) != AC97_EXT_DACS)
						return -EINVAL;
					break;
				default:
					return -EINVAL;
				}

				stop_dac(s);
				if (val <= 2 &&
				    (s->codec_ext_caps & AC97_EXT_DACS)) {
					/* disable surround and center/lfe
					 * channels in AC'97
					 */
					u16             ext_stat =
						rdcodec(s->codec,
							AC97_EXTENDED_STATUS);
					wrcodec(s->codec,
						AC97_EXTENDED_STATUS,
						ext_stat | (AC97_EXTSTAT_PRI |
							    AC97_EXTSTAT_PRJ |
							    AC97_EXTSTAT_PRK));
				} else if (val >= 4) {
					/* enable surround, center/lfe
					 * channels in AC'97
					 */
					u16             ext_stat =
						rdcodec(s->codec,
							AC97_EXTENDED_STATUS);
					ext_stat &= ~AC97_EXTSTAT_PRJ;
					if (val == 6)
						ext_stat &=
							~(AC97_EXTSTAT_PRI |
							  AC97_EXTSTAT_PRK);
					wrcodec(s->codec,
						AC97_EXTENDED_STATUS,
						ext_stat);
				}

				s->dma_dac.num_channels = val;
				if ((ret = prog_dmabuf_dac(s)))
					return ret;
			}
		}
		return put_user(val, (int *) arg);

	case SNDCTL_DSP_GETFMTS:	/* Returns a mask */
		return put_user(AFMT_S16_LE | AFMT_U8, (int *) arg);

	case SNDCTL_DSP_SETFMT:	/* Selects ONE fmt */
		if (get_user(val, (int *) arg))
			return -EFAULT;
		if (val != AFMT_QUERY) {
			if (file->f_mode & FMODE_READ) {
				stop_adc(s);
				if (val == AFMT_S16_LE)
					s->dma_adc.sample_size = 16;
				else {
					val = AFMT_U8;
					s->dma_adc.sample_size = 8;
				}
				if ((ret = prog_dmabuf_adc(s)))
					return ret;
			}
			if (file->f_mode & FMODE_WRITE) {
				stop_dac(s);
				if (val == AFMT_S16_LE)
					s->dma_dac.sample_size = 16;
				else {
					val = AFMT_U8;
					s->dma_dac.sample_size = 8;
				}
				if ((ret = prog_dmabuf_dac(s)))
					return ret;
			}
		} else {
			if (file->f_mode & FMODE_READ)
				val = (s->dma_adc.sample_size == 16) ?
					AFMT_S16_LE : AFMT_U8;
			else
				val = (s->dma_dac.sample_size == 16) ?
					AFMT_S16_LE : AFMT_U8;
		}
		return put_user(val, (int *) arg);

	case SNDCTL_DSP_POST:
		return 0;

	case SNDCTL_DSP_GETTRIGGER:
		val = 0;
		spin_lock_irqsave(&s->lock, flags);
		if (file->f_mode & FMODE_READ && !s->dma_adc.stopped)
			val |= PCM_ENABLE_INPUT;
		if (file->f_mode & FMODE_WRITE && !s->dma_dac.stopped)
			val |= PCM_ENABLE_OUTPUT;
		spin_unlock_irqrestore(&s->lock, flags);
		return put_user(val, (int *) arg);

	case SNDCTL_DSP_SETTRIGGER:
		if (get_user(val, (int *) arg))
			return -EFAULT;
		if (file->f_mode & FMODE_READ) {
			if (val & PCM_ENABLE_INPUT) {
				spin_lock_irqsave(&s->lock, flags);
				start_adc(s);
				spin_unlock_irqrestore(&s->lock, flags);
			} else
				stop_adc(s);
		}
		if (file->f_mode & FMODE_WRITE) {
			if (val & PCM_ENABLE_OUTPUT) {
				spin_lock_irqsave(&s->lock, flags);
				start_dac(s);
				spin_unlock_irqrestore(&s->lock, flags);
			} else
				stop_dac(s);
		}
		return 0;

	case SNDCTL_DSP_GETOSPACE:
		if (!(file->f_mode & FMODE_WRITE))
			return -EINVAL;
		abinfo.fragsize = s->dma_dac.fragsize;
		spin_lock_irqsave(&s->lock, flags);
		count = s->dma_dac.count;
		count -= dma_count_done(&s->dma_dac);
		spin_unlock_irqrestore(&s->lock, flags);
		if (count < 0)
			count = 0;
		abinfo.bytes = (s->dma_dac.dmasize - count) /
			s->dma_dac.cnt_factor;
		abinfo.fragstotal = s->dma_dac.numfrag;
		abinfo.fragments = abinfo.bytes >> s->dma_dac.fragshift;
		pr_debug("ioctl SNDCTL_DSP_GETOSPACE: bytes=%d, fragments=%d\n", abinfo.bytes, abinfo.fragments);
		return copy_to_user((void *) arg, &abinfo,
				    sizeof(abinfo)) ? -EFAULT : 0;

	case SNDCTL_DSP_GETISPACE:
		if (!(file->f_mode & FMODE_READ))
			return -EINVAL;
		abinfo.fragsize = s->dma_adc.fragsize;
		spin_lock_irqsave(&s->lock, flags);
		count = s->dma_adc.count;
		count += dma_count_done(&s->dma_adc);
		spin_unlock_irqrestore(&s->lock, flags);
		if (count < 0)
			count = 0;
		abinfo.bytes = count / s->dma_adc.cnt_factor;
		abinfo.fragstotal = s->dma_adc.numfrag;
		abinfo.fragments = abinfo.bytes >> s->dma_adc.fragshift;
		return copy_to_user((void *) arg, &abinfo,
				    sizeof(abinfo)) ? -EFAULT : 0;

	case SNDCTL_DSP_NONBLOCK:
		spin_lock(&file->f_lock);
		file->f_flags |= O_NONBLOCK;
		spin_unlock(&file->f_lock);
		return 0;

	case SNDCTL_DSP_GETODELAY:
		if (!(file->f_mode & FMODE_WRITE))
			return -EINVAL;
		spin_lock_irqsave(&s->lock, flags);
		count = s->dma_dac.count;
		count -= dma_count_done(&s->dma_dac);
		spin_unlock_irqrestore(&s->lock, flags);
		if (count < 0)
			count = 0;
		count /= s->dma_dac.cnt_factor;
		return put_user(count, (int *) arg);

	case SNDCTL_DSP_GETIPTR:
		if (!(file->f_mode & FMODE_READ))
			return -EINVAL;
		spin_lock_irqsave(&s->lock, flags);
		cinfo.bytes = s->dma_adc.total_bytes;
		count = s->dma_adc.count;
		if (!s->dma_adc.stopped) {
			diff = dma_count_done(&s->dma_adc);
			count += diff;
			cinfo.bytes += diff;
			cinfo.ptr =  virt_to_phys(s->dma_adc.nextIn) + diff -
				virt_to_phys(s->dma_adc.rawbuf);
		} else
			cinfo.ptr = virt_to_phys(s->dma_adc.nextIn) -
				virt_to_phys(s->dma_adc.rawbuf);
		if (s->dma_adc.mapped)
			s->dma_adc.count &= (s->dma_adc.dma_fragsize-1);
		spin_unlock_irqrestore(&s->lock, flags);
		if (count < 0)
			count = 0;
		cinfo.blocks = count >> s->dma_adc.fragshift;
		return copy_to_user((void *) arg, &cinfo, sizeof(cinfo));

	case SNDCTL_DSP_GETOPTR:
		if (!(file->f_mode & FMODE_READ))
			return -EINVAL;
		spin_lock_irqsave(&s->lock, flags);
		cinfo.bytes = s->dma_dac.total_bytes;
		count = s->dma_dac.count;
		if (!s->dma_dac.stopped) {
			diff = dma_count_done(&s->dma_dac);
			count -= diff;
			cinfo.bytes += diff;
			cinfo.ptr = virt_to_phys(s->dma_dac.nextOut) + diff -
				virt_to_phys(s->dma_dac.rawbuf);
		} else
			cinfo.ptr = virt_to_phys(s->dma_dac.nextOut) -
				virt_to_phys(s->dma_dac.rawbuf);
		if (s->dma_dac.mapped)
			s->dma_dac.count &= (s->dma_dac.dma_fragsize-1);
		spin_unlock_irqrestore(&s->lock, flags);
		if (count < 0)
			count = 0;
		cinfo.blocks = count >> s->dma_dac.fragshift;
		return copy_to_user((void *) arg, &cinfo, sizeof(cinfo));

	case SNDCTL_DSP_GETBLKSIZE:
		if (file->f_mode & FMODE_WRITE)
			return put_user(s->dma_dac.fragsize, (int *) arg);
		else
			return put_user(s->dma_adc.fragsize, (int *) arg);

	case SNDCTL_DSP_SETFRAGMENT:
		if (get_user(val, (int *) arg))
			return -EFAULT;
		if (file->f_mode & FMODE_READ) {
			stop_adc(s);
			s->dma_adc.ossfragshift = val & 0xffff;
			s->dma_adc.ossmaxfrags = (val >> 16) & 0xffff;
			if (s->dma_adc.ossfragshift < 4)
				s->dma_adc.ossfragshift = 4;
			if (s->dma_adc.ossfragshift > 15)
				s->dma_adc.ossfragshift = 15;
			if (s->dma_adc.ossmaxfrags < 4)
				s->dma_adc.ossmaxfrags = 4;
			if ((ret = prog_dmabuf_adc(s)))
				return ret;
		}
		if (file->f_mode & FMODE_WRITE) {
			stop_dac(s);
			s->dma_dac.ossfragshift = val & 0xffff;
			s->dma_dac.ossmaxfrags = (val >> 16) & 0xffff;
			if (s->dma_dac.ossfragshift < 4)
				s->dma_dac.ossfragshift = 4;
			if (s->dma_dac.ossfragshift > 15)
				s->dma_dac.ossfragshift = 15;
			if (s->dma_dac.ossmaxfrags < 4)
				s->dma_dac.ossmaxfrags = 4;
			if ((ret = prog_dmabuf_dac(s)))
				return ret;
		}
		return 0;

	case SNDCTL_DSP_SUBDIVIDE:
		if ((file->f_mode & FMODE_READ && s->dma_adc.subdivision) ||
		    (file->f_mode & FMODE_WRITE && s->dma_dac.subdivision))
			return -EINVAL;
		if (get_user(val, (int *) arg))
			return -EFAULT;
		if (val != 1 && val != 2 && val != 4)
			return -EINVAL;
		if (file->f_mode & FMODE_READ) {
			stop_adc(s);
			s->dma_adc.subdivision = val;
			if ((ret = prog_dmabuf_adc(s)))
				return ret;
		}
		if (file->f_mode & FMODE_WRITE) {
			stop_dac(s);
			s->dma_dac.subdivision = val;
			if ((ret = prog_dmabuf_dac(s)))
				return ret;
		}
		return 0;

	case SOUND_PCM_READ_RATE:
		return put_user((file->f_mode & FMODE_READ) ?
				s->dma_adc.sample_rate :
				s->dma_dac.sample_rate,
				(int *)arg);

	case SOUND_PCM_READ_CHANNELS:
		if (file->f_mode & FMODE_READ)
			return put_user(s->dma_adc.num_channels, (int *)arg);
		else
			return put_user(s->dma_dac.num_channels, (int *)arg);

	case SOUND_PCM_READ_BITS:
		if (file->f_mode & FMODE_READ)
			return put_user(s->dma_adc.sample_size, (int *)arg);
		else
			return put_user(s->dma_dac.sample_size, (int *)arg);

	case SOUND_PCM_WRITE_FILTER:
	case SNDCTL_DSP_SETSYNCRO:
	case SOUND_PCM_READ_FILTER:
		return -EINVAL;
	}

	return mixdev_ioctl(s->codec, cmd, arg);
}