#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; TYPE_2__ cam; } ;
struct sd {int sensor; int sensor_width; int sensor_height; struct gspca_dev gspca_dev; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
#define  SEN_OV2610 141 
#define  SEN_OV3610 140 
#define  SEN_OV6620 139 
#define  SEN_OV6630 138 
#define  SEN_OV66308AF 137 
#define  SEN_OV7610 136 
#define  SEN_OV7620 135 
#define  SEN_OV7620AE 134 
#define  SEN_OV7640 133 
#define  SEN_OV7648 132 
#define  SEN_OV7660 131 
#define  SEN_OV7670 130 
#define  SEN_OV76BE 129 
#define  SEN_OV8610 128 
 int /*<<< orphan*/  i2c_w (struct sd*,int,int) ; 
 int /*<<< orphan*/  mode_init_ov_sensor_regs (struct sd*) ; 
 int /*<<< orphan*/  ov519_set_fr (struct sd*) ; 
 int /*<<< orphan*/  ov519_set_mode (struct sd*) ; 

__attribute__((used)) static void set_ov_sensor_window(struct sd *sd)
{
	struct gspca_dev *gspca_dev;
	int qvga, crop;
	int hwsbase, hwebase, vwsbase, vwebase, hwscale, vwscale;

	/* mode setup is fully handled in mode_init_ov_sensor_regs for these */
	switch (sd->sensor) {
	case SEN_OV2610:
	case SEN_OV3610:
	case SEN_OV7670:
		mode_init_ov_sensor_regs(sd);
		return;
	case SEN_OV7660:
		ov519_set_mode(sd);
		ov519_set_fr(sd);
		return;
	}

	gspca_dev = &sd->gspca_dev;
	qvga = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv & 1;
	crop = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv & 2;

	/* The different sensor ICs handle setting up of window differently.
	 * IF YOU SET IT WRONG, YOU WILL GET ALL ZERO ISOC DATA FROM OV51x!! */
	switch (sd->sensor) {
	case SEN_OV8610:
		hwsbase = 0x1e;
		hwebase = 0x1e;
		vwsbase = 0x02;
		vwebase = 0x02;
		break;
	case SEN_OV7610:
	case SEN_OV76BE:
		hwsbase = 0x38;
		hwebase = 0x3a;
		vwsbase = vwebase = 0x05;
		break;
	case SEN_OV6620:
	case SEN_OV6630:
	case SEN_OV66308AF:
		hwsbase = 0x38;
		hwebase = 0x3a;
		vwsbase = 0x05;
		vwebase = 0x06;
		if (sd->sensor == SEN_OV66308AF && qvga)
			/* HDG: this fixes U and V getting swapped */
			hwsbase++;
		if (crop) {
			hwsbase += 8;
			hwebase += 8;
			vwsbase += 11;
			vwebase += 11;
		}
		break;
	case SEN_OV7620:
	case SEN_OV7620AE:
		hwsbase = 0x2f;		/* From 7620.SET (spec is wrong) */
		hwebase = 0x2f;
		vwsbase = vwebase = 0x05;
		break;
	case SEN_OV7640:
	case SEN_OV7648:
		hwsbase = 0x1a;
		hwebase = 0x1a;
		vwsbase = vwebase = 0x03;
		break;
	default:
		return;
	}

	switch (sd->sensor) {
	case SEN_OV6620:
	case SEN_OV6630:
	case SEN_OV66308AF:
		if (qvga) {		/* QCIF */
			hwscale = 0;
			vwscale = 0;
		} else {		/* CIF */
			hwscale = 1;
			vwscale = 1;	/* The datasheet says 0;
					 * it's wrong */
		}
		break;
	case SEN_OV8610:
		if (qvga) {		/* QSVGA */
			hwscale = 1;
			vwscale = 1;
		} else {		/* SVGA */
			hwscale = 2;
			vwscale = 2;
		}
		break;
	default:			/* SEN_OV7xx0 */
		if (qvga) {		/* QVGA */
			hwscale = 1;
			vwscale = 0;
		} else {		/* VGA */
			hwscale = 2;
			vwscale = 1;
		}
	}

	mode_init_ov_sensor_regs(sd);

	i2c_w(sd, 0x17, hwsbase);
	i2c_w(sd, 0x18, hwebase + (sd->sensor_width >> hwscale));
	i2c_w(sd, 0x19, vwsbase);
	i2c_w(sd, 0x1a, vwebase + (sd->sensor_height >> vwscale));
}