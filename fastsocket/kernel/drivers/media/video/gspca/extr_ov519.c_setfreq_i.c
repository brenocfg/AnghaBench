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
struct sd {scalar_t__ sensor; TYPE_1__* ctrls; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 size_t FREQ ; 
 int OV7670_COM11_HZAUTO ; 
 int OV7670_COM8_BFILT ; 
 int OV7670_R13_COM8 ; 
 int OV7670_R3B_COM11 ; 
 scalar_t__ SEN_OV6620 ; 
 scalar_t__ SEN_OV6630 ; 
 scalar_t__ SEN_OV66308AF ; 
 scalar_t__ SEN_OV7660 ; 
 scalar_t__ SEN_OV7670 ; 
 int /*<<< orphan*/  i2c_w (struct sd*,int,int) ; 
 int /*<<< orphan*/  i2c_w_mask (struct sd*,int,int,int) ; 

__attribute__((used)) static void setfreq_i(struct sd *sd)
{
	if (sd->sensor == SEN_OV7660
	 || sd->sensor == SEN_OV7670) {
		switch (sd->ctrls[FREQ].val) {
		case 0: /* Banding filter disabled */
			i2c_w_mask(sd, OV7670_R13_COM8, 0, OV7670_COM8_BFILT);
			break;
		case 1: /* 50 hz */
			i2c_w_mask(sd, OV7670_R13_COM8, OV7670_COM8_BFILT,
				   OV7670_COM8_BFILT);
			i2c_w_mask(sd, OV7670_R3B_COM11, 0x08, 0x18);
			break;
		case 2: /* 60 hz */
			i2c_w_mask(sd, OV7670_R13_COM8, OV7670_COM8_BFILT,
				   OV7670_COM8_BFILT);
			i2c_w_mask(sd, OV7670_R3B_COM11, 0x00, 0x18);
			break;
		case 3: /* Auto hz - ov7670 only */
			i2c_w_mask(sd, OV7670_R13_COM8, OV7670_COM8_BFILT,
				   OV7670_COM8_BFILT);
			i2c_w_mask(sd, OV7670_R3B_COM11, OV7670_COM11_HZAUTO,
				   0x18);
			break;
		}
	} else {
		switch (sd->ctrls[FREQ].val) {
		case 0: /* Banding filter disabled */
			i2c_w_mask(sd, 0x2d, 0x00, 0x04);
			i2c_w_mask(sd, 0x2a, 0x00, 0x80);
			break;
		case 1: /* 50 hz (filter on and framerate adj) */
			i2c_w_mask(sd, 0x2d, 0x04, 0x04);
			i2c_w_mask(sd, 0x2a, 0x80, 0x80);
			/* 20 fps -> 16.667 fps */
			if (sd->sensor == SEN_OV6620 ||
			    sd->sensor == SEN_OV6630 ||
			    sd->sensor == SEN_OV66308AF)
				i2c_w(sd, 0x2b, 0x5e);
			else
				i2c_w(sd, 0x2b, 0xac);
			break;
		case 2: /* 60 hz (filter on, ...) */
			i2c_w_mask(sd, 0x2d, 0x04, 0x04);
			if (sd->sensor == SEN_OV6620 ||
			    sd->sensor == SEN_OV6630 ||
			    sd->sensor == SEN_OV66308AF) {
				/* 20 fps -> 15 fps */
				i2c_w_mask(sd, 0x2a, 0x80, 0x80);
				i2c_w(sd, 0x2b, 0xa8);
			} else {
				/* no framerate adj. */
				i2c_w_mask(sd, 0x2a, 0x00, 0x80);
			}
			break;
		}
	}
}