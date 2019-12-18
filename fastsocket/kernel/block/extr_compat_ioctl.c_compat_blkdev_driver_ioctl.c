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
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
#define  BLKSECTSET 219 
#define  CDROMCLOSETRAY 218 
#define  CDROMEJECT 217 
#define  CDROMEJECT_SW 216 
#define  CDROMMULTISESSION 215 
#define  CDROMPAUSE 214 
#define  CDROMPLAYBLK 213 
#define  CDROMPLAYMSF 212 
#define  CDROMPLAYTRKIND 211 
#define  CDROMREADALL 210 
#define  CDROMREADAUDIO 209 
#define  CDROMREADCOOKED 208 
#define  CDROMREADMODE1 207 
#define  CDROMREADMODE2 206 
#define  CDROMREADRAW 205 
#define  CDROMREADTOCENTRY 204 
#define  CDROMREADTOCHDR 203 
#define  CDROMRESET 202 
#define  CDROMRESUME 201 
#define  CDROMSEEK 200 
#define  CDROMSTART 199 
#define  CDROMSTOP 198 
#define  CDROMSUBCHNL 197 
#define  CDROMVOLCTRL 196 
#define  CDROMVOLREAD 195 
#define  CDROM_CHANGER_NSLOTS 194 
#define  CDROM_CLEAR_OPTIONS 193 
#define  CDROM_DEBUG 192 
#define  CDROM_DISC_STATUS 191 
#define  CDROM_DRIVE_STATUS 190 
#define  CDROM_GET_CAPABILITY 189 
#define  CDROM_GET_MCN 188 
#define  CDROM_LOCKDOOR 187 
#define  CDROM_MEDIA_CHANGED 186 
#define  CDROM_SELECT_DISC 185 
#define  CDROM_SELECT_SPEED 184 
#define  CDROM_SEND_PACKET 183 
#define  CDROM_SET_OPTIONS 182 
#define  DVD_AUTH 181 
#define  DVD_READ_STRUCT 180 
#define  DVD_WRITE_STRUCT 179 
 int ENOIOCTLCMD ; 
#define  FDCLRPRM 178 
#define  FDDEFPRM32 177 
#define  FDEJECT 176 
#define  FDFLUSH 175 
#define  FDFMTBEG 174 
#define  FDFMTEND 173 
#define  FDFMTTRK 172 
#define  FDGETDRVPRM32 171 
#define  FDGETDRVSTAT32 170 
#define  FDGETDRVTYP 169 
#define  FDGETFDCSTAT32 168 
#define  FDGETMAXERRS 167 
#define  FDGETPRM32 166 
#define  FDMSGOFF 165 
#define  FDMSGON 164 
#define  FDPOLLDRVSTAT32 163 
#define  FDRAWCMD 162 
#define  FDRESET 161 
#define  FDSETDRVPRM32 160 
#define  FDSETEMSGTRESH 159 
#define  FDSETMAXERRS 158 
#define  FDSETPRM32 157 
#define  FDTWADDLE 156 
#define  FDWERRORCLR 155 
#define  FDWERRORGET32 154 
#define  HDIO_DRIVE_CMD 153 
#define  HDIO_DRIVE_TASK 152 
#define  HDIO_GET_32BIT 151 
#define  HDIO_GET_ACOUSTIC 150 
#define  HDIO_GET_ADDRESS 149 
#define  HDIO_GET_BUSSTATE 148 
#define  HDIO_GET_DMA 147 
#define  HDIO_GET_IDENTITY 146 
#define  HDIO_GET_KEEPSETTINGS 145 
#define  HDIO_GET_MULTCOUNT 144 
#define  HDIO_GET_NICE 143 
#define  HDIO_GET_NOWERR 142 
#define  HDIO_GET_UNMASKINTR 141 
#define  HDIO_GET_WCACHE 140 
#define  HDIO_SET_32BIT 139 
#define  HDIO_SET_ACOUSTIC 138 
#define  HDIO_SET_ADDRESS 137 
#define  HDIO_SET_BUSSTATE 136 
#define  HDIO_SET_DMA 135 
#define  HDIO_SET_KEEPSETTINGS 134 
#define  HDIO_SET_MULTCOUNT 133 
#define  HDIO_SET_NICE 132 
#define  HDIO_SET_NOWERR 131 
#define  HDIO_SET_PIO_MODE 130 
#define  HDIO_SET_UNMASKINTR 129 
#define  HDIO_SET_WCACHE 128 
 int __blkdev_driver_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int compat_cdrom_generic_command (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int compat_cdrom_read_audio (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int compat_fd_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 int compat_hdio_ioctl (struct block_device*,int /*<<< orphan*/ ,unsigned int,unsigned long) ; 
 scalar_t__ compat_ptr (unsigned long) ; 

__attribute__((used)) static int compat_blkdev_driver_ioctl(struct block_device *bdev, fmode_t mode,
			unsigned cmd, unsigned long arg)
{
	switch (cmd) {
	case HDIO_GET_UNMASKINTR:
	case HDIO_GET_MULTCOUNT:
	case HDIO_GET_KEEPSETTINGS:
	case HDIO_GET_32BIT:
	case HDIO_GET_NOWERR:
	case HDIO_GET_DMA:
	case HDIO_GET_NICE:
	case HDIO_GET_WCACHE:
	case HDIO_GET_ACOUSTIC:
	case HDIO_GET_ADDRESS:
	case HDIO_GET_BUSSTATE:
		return compat_hdio_ioctl(bdev, mode, cmd, arg);
	case FDSETPRM32:
	case FDDEFPRM32:
	case FDGETPRM32:
	case FDSETDRVPRM32:
	case FDGETDRVPRM32:
	case FDGETDRVSTAT32:
	case FDPOLLDRVSTAT32:
	case FDGETFDCSTAT32:
	case FDWERRORGET32:
		return compat_fd_ioctl(bdev, mode, cmd, arg);
	case CDROMREADAUDIO:
		return compat_cdrom_read_audio(bdev, mode, cmd, arg);
	case CDROM_SEND_PACKET:
		return compat_cdrom_generic_command(bdev, mode, cmd, arg);

	/*
	 * No handler required for the ones below, we just need to
	 * convert arg to a 64 bit pointer.
	 */
	case BLKSECTSET:
	/*
	 * 0x03 -- HD/IDE ioctl's used by hdparm and friends.
	 *         Some need translations, these do not.
	 */
	case HDIO_GET_IDENTITY:
	case HDIO_DRIVE_TASK:
	case HDIO_DRIVE_CMD:
	/* 0x330 is reserved -- it used to be HDIO_GETGEO_BIG */
	case 0x330:
	/* 0x02 -- Floppy ioctls */
	case FDMSGON:
	case FDMSGOFF:
	case FDSETEMSGTRESH:
	case FDFLUSH:
	case FDWERRORCLR:
	case FDSETMAXERRS:
	case FDGETMAXERRS:
	case FDGETDRVTYP:
	case FDEJECT:
	case FDCLRPRM:
	case FDFMTBEG:
	case FDFMTEND:
	case FDRESET:
	case FDTWADDLE:
	case FDFMTTRK:
	case FDRAWCMD:
	/* CDROM stuff */
	case CDROMPAUSE:
	case CDROMRESUME:
	case CDROMPLAYMSF:
	case CDROMPLAYTRKIND:
	case CDROMREADTOCHDR:
	case CDROMREADTOCENTRY:
	case CDROMSTOP:
	case CDROMSTART:
	case CDROMEJECT:
	case CDROMVOLCTRL:
	case CDROMSUBCHNL:
	case CDROMMULTISESSION:
	case CDROM_GET_MCN:
	case CDROMRESET:
	case CDROMVOLREAD:
	case CDROMSEEK:
	case CDROMPLAYBLK:
	case CDROMCLOSETRAY:
	case CDROM_DISC_STATUS:
	case CDROM_CHANGER_NSLOTS:
	case CDROM_GET_CAPABILITY:
	/* Ignore cdrom.h about these next 5 ioctls, they absolutely do
	 * not take a struct cdrom_read, instead they take a struct cdrom_msf
	 * which is compatible.
	 */
	case CDROMREADMODE2:
	case CDROMREADMODE1:
	case CDROMREADRAW:
	case CDROMREADCOOKED:
	case CDROMREADALL:
	/* DVD ioctls */
	case DVD_READ_STRUCT:
	case DVD_WRITE_STRUCT:
	case DVD_AUTH:
		arg = (unsigned long)compat_ptr(arg);
	/* These intepret arg as an unsigned long, not as a pointer,
	 * so we must not do compat_ptr() conversion. */
	case HDIO_SET_MULTCOUNT:
	case HDIO_SET_UNMASKINTR:
	case HDIO_SET_KEEPSETTINGS:
	case HDIO_SET_32BIT:
	case HDIO_SET_NOWERR:
	case HDIO_SET_DMA:
	case HDIO_SET_PIO_MODE:
	case HDIO_SET_NICE:
	case HDIO_SET_WCACHE:
	case HDIO_SET_ACOUSTIC:
	case HDIO_SET_BUSSTATE:
	case HDIO_SET_ADDRESS:
	case CDROMEJECT_SW:
	case CDROM_SET_OPTIONS:
	case CDROM_CLEAR_OPTIONS:
	case CDROM_SELECT_SPEED:
	case CDROM_SELECT_DISC:
	case CDROM_MEDIA_CHANGED:
	case CDROM_DRIVE_STATUS:
	case CDROM_LOCKDOOR:
	case CDROM_DEBUG:
		break;
	default:
		/* unknown ioctl number */
		return -ENOIOCTLCMD;
	}

	return __blkdev_driver_ioctl(bdev, mode, cmd, arg);
}