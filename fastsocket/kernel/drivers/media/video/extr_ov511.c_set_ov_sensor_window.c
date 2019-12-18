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
struct usb_ov511 {int sensor; scalar_t__ bclass; int subx; int subw; int suby; int subh; } ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int EINVAL ; 
#define  SEN_OV6620 132 
#define  SEN_OV6630 131 
#define  SEN_OV7610 130 
#define  SEN_OV7620 129 
#define  SEN_OV76BE 128 
 int /*<<< orphan*/  dump_i2c_regs (struct usb_ov511*) ; 
 scalar_t__ dump_sensor ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  i2c_w (struct usb_ov511*,int,int) ; 
 int mode_init_ov_sensor_regs (struct usb_ov511*,int,int,int,int,int) ; 

__attribute__((used)) static int
set_ov_sensor_window(struct usb_ov511 *ov, int width, int height, int mode,
		     int sub_flag)
{
	int ret;
	int hwsbase, hwebase, vwsbase, vwebase, hwsize, vwsize;
	int hoffset, voffset, hwscale = 0, vwscale = 0;

	/* The different sensor ICs handle setting up of window differently.
	 * IF YOU SET IT WRONG, YOU WILL GET ALL ZERO ISOC DATA FROM OV51x!!! */
	switch (ov->sensor) {
	case SEN_OV7610:
	case SEN_OV76BE:
		hwsbase = 0x38;
		hwebase = 0x3a;
		vwsbase = vwebase = 0x05;
		break;
	case SEN_OV6620:
	case SEN_OV6630:
		hwsbase = 0x38;
		hwebase = 0x3a;
		vwsbase = 0x05;
		vwebase = 0x06;
		break;
	case SEN_OV7620:
		hwsbase = 0x2f;		/* From 7620.SET (spec is wrong) */
		hwebase = 0x2f;
		vwsbase = vwebase = 0x05;
		break;
	default:
		err("Invalid sensor");
		return -EINVAL;
	}

	if (ov->sensor == SEN_OV6620 || ov->sensor == SEN_OV6630) {
		/* Note: OV518(+) does downsample on its own) */
		if ((width > 176 && height > 144)
		    || ov->bclass == BCL_OV518) {  /* CIF */
			ret = mode_init_ov_sensor_regs(ov, width, height,
				mode, sub_flag, 0);
			if (ret < 0)
				return ret;
			hwscale = 1;
			vwscale = 1;  /* The datasheet says 0; it's wrong */
			hwsize = 352;
			vwsize = 288;
		} else if (width > 176 || height > 144) {
			err("Illegal dimensions");
			return -EINVAL;
		} else {			    /* QCIF */
			ret = mode_init_ov_sensor_regs(ov, width, height,
				mode, sub_flag, 1);
			if (ret < 0)
				return ret;
			hwsize = 176;
			vwsize = 144;
		}
	} else {
		if (width > 320 && height > 240) {  /* VGA */
			ret = mode_init_ov_sensor_regs(ov, width, height,
				mode, sub_flag, 0);
			if (ret < 0)
				return ret;
			hwscale = 2;
			vwscale = 1;
			hwsize = 640;
			vwsize = 480;
		} else if (width > 320 || height > 240) {
			err("Illegal dimensions");
			return -EINVAL;
		} else {			    /* QVGA */
			ret = mode_init_ov_sensor_regs(ov, width, height,
				mode, sub_flag, 1);
			if (ret < 0)
				return ret;
			hwscale = 1;
			hwsize = 320;
			vwsize = 240;
		}
	}

	/* Center the window */
	hoffset = ((hwsize - width) / 2) >> hwscale;
	voffset = ((vwsize - height) / 2) >> vwscale;

	/* FIXME! - This needs to be changed to support 160x120 and 6620!!! */
	if (sub_flag) {
		i2c_w(ov, 0x17, hwsbase+(ov->subx>>hwscale));
		i2c_w(ov, 0x18,	hwebase+((ov->subx+ov->subw)>>hwscale));
		i2c_w(ov, 0x19, vwsbase+(ov->suby>>vwscale));
		i2c_w(ov, 0x1a, vwebase+((ov->suby+ov->subh)>>vwscale));
	} else {
		i2c_w(ov, 0x17, hwsbase + hoffset);
		i2c_w(ov, 0x18, hwebase + hoffset + (hwsize>>hwscale));
		i2c_w(ov, 0x19, vwsbase + voffset);
		i2c_w(ov, 0x1a, vwebase + voffset + (vwsize>>vwscale));
	}

#ifdef OV511_DEBUG
	if (dump_sensor)
		dump_i2c_regs(ov);
#endif

	return 0;
}