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
typedef  int u8 ;
struct sd {int sensor; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int QUANT_VAL ; 
#define  SENSOR_ADCM2700 133 
#define  SENSOR_GC0305 132 
#define  SENSOR_HV7131B 131 
#define  SENSOR_OV7620 130 
#define  SENSOR_PAS202B 129 
#define  SENSOR_PO2030 128 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setquality(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 frxt;

	switch (sd->sensor) {
	case SENSOR_ADCM2700:
	case SENSOR_GC0305:
	case SENSOR_HV7131B:
	case SENSOR_OV7620:
	case SENSOR_PAS202B:
	case SENSOR_PO2030:
		return;
	}
/*fixme: is it really 0008 0007 0018 for all other sensors? */
	reg_w(gspca_dev, QUANT_VAL, 0x0008);
	frxt = 0x30;
	reg_w(gspca_dev, frxt, 0x0007);
#if QUANT_VAL == 0 || QUANT_VAL == 1 || QUANT_VAL == 2
	frxt = 0xff;
#elif QUANT_VAL == 3
	frxt = 0xf0;
#elif QUANT_VAL == 4
	frxt = 0xe0;
#else
	frxt = 0x20;
#endif
	reg_w(gspca_dev, frxt, 0x0018);
}