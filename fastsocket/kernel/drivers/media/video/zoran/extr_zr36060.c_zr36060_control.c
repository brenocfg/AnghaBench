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
struct jpeg_com_marker {int dummy; } ;
struct jpeg_app_marker {int dummy; } ;
struct zr36060 {int status; int total_code_vol; int real_code_vol; int scalefact; struct jpeg_com_marker com; struct jpeg_app_marker app; int /*<<< orphan*/  name; } ;
struct videocodec {scalar_t__ data; } ;

/* Variables and functions */
#define  CODEC_G_CODEC_MODE 141 
#define  CODEC_G_JPEG_APP_DATA 140 
#define  CODEC_G_JPEG_COM_DATA 139 
#define  CODEC_G_JPEG_SCALE 138 
#define  CODEC_G_JPEG_TDS_BYTE 137 
#define  CODEC_G_STATUS 136 
#define  CODEC_G_VFE 135 
 int CODEC_MODE_BJPG ; 
#define  CODEC_S_CODEC_MODE 134 
#define  CODEC_S_JPEG_APP_DATA 133 
#define  CODEC_S_JPEG_COM_DATA 132 
#define  CODEC_S_JPEG_SCALE 131 
#define  CODEC_S_JPEG_TDS_BYTE 130 
#define  CODEC_S_MMAP 129 
#define  CODEC_S_VFE 128 
 int EFAULT ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int,int) ; 
 int zr36060_read_scalefactor (struct zr36060*) ; 
 int /*<<< orphan*/  zr36060_read_status (struct zr36060*) ; 

__attribute__((used)) static int
zr36060_control (struct videocodec *codec,
		 int                type,
		 int                size,
		 void              *data)
{
	struct zr36060 *ptr = (struct zr36060 *) codec->data;
	int *ival = (int *) data;

	dprintk(2, "%s: control %d call with %d byte\n", ptr->name, type,
		size);

	switch (type) {
	case CODEC_G_STATUS:	/* get last status */
		if (size != sizeof(int))
			return -EFAULT;
		zr36060_read_status(ptr);
		*ival = ptr->status;
		break;

	case CODEC_G_CODEC_MODE:
		if (size != sizeof(int))
			return -EFAULT;
		*ival = CODEC_MODE_BJPG;
		break;

	case CODEC_S_CODEC_MODE:
		if (size != sizeof(int))
			return -EFAULT;
		if (*ival != CODEC_MODE_BJPG)
			return -EINVAL;
		/* not needed, do nothing */
		return 0;

	case CODEC_G_VFE:
	case CODEC_S_VFE:
		/* not needed, do nothing */
		return 0;

	case CODEC_S_MMAP:
		/* not available, give an error */
		return -ENXIO;

	case CODEC_G_JPEG_TDS_BYTE:	/* get target volume in byte */
		if (size != sizeof(int))
			return -EFAULT;
		*ival = ptr->total_code_vol;
		break;

	case CODEC_S_JPEG_TDS_BYTE:	/* get target volume in byte */
		if (size != sizeof(int))
			return -EFAULT;
		ptr->total_code_vol = *ival;
		ptr->real_code_vol = (ptr->total_code_vol * 6) >> 3;
		break;

	case CODEC_G_JPEG_SCALE:	/* get scaling factor */
		if (size != sizeof(int))
			return -EFAULT;
		*ival = zr36060_read_scalefactor(ptr);
		break;

	case CODEC_S_JPEG_SCALE:	/* set scaling factor */
		if (size != sizeof(int))
			return -EFAULT;
		ptr->scalefact = *ival;
		break;

	case CODEC_G_JPEG_APP_DATA: {	/* get appn marker data */
		struct jpeg_app_marker *app = data;

		if (size != sizeof(struct jpeg_app_marker))
			return -EFAULT;

		*app = ptr->app;
		break;
	}

	case CODEC_S_JPEG_APP_DATA: {	/* set appn marker data */
		struct jpeg_app_marker *app = data;

		if (size != sizeof(struct jpeg_app_marker))
			return -EFAULT;

		ptr->app = *app;
		break;
	}

	case CODEC_G_JPEG_COM_DATA: {	/* get comment marker data */
		struct jpeg_com_marker *com = data;

		if (size != sizeof(struct jpeg_com_marker))
			return -EFAULT;

		*com = ptr->com;
		break;
	}

	case CODEC_S_JPEG_COM_DATA: {	/* set comment marker data */
		struct jpeg_com_marker *com = data;

		if (size != sizeof(struct jpeg_com_marker))
			return -EFAULT;

		ptr->com = *com;
		break;
	}

	default:
		return -EINVAL;
	}

	return size;
}