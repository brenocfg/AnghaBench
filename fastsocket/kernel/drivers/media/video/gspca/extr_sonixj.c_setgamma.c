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
typedef  int u8 ;
struct sd {int sensor; TYPE_1__* ctrls; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 size_t GAMMA ; 
 int GAMMA_DEF ; 
#define  SENSOR_ADCM1700 133 
#define  SENSOR_GC0307 132 
#define  SENSOR_HV7131R 131 
#define  SENSOR_MI0360B 130 
#define  SENSOR_MT9V111 129 
#define  SENSOR_SP80708 128 
 int* gamma_def ; 
 int* gamma_spec_0 ; 
 int* gamma_spec_1 ; 
 int* gamma_spec_2 ; 
 int* gamma_spec_3 ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void setgamma(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i, val;
	u8 gamma[17];
	const u8 *gamma_base;
	static const u8 delta[17] = {
		0x00, 0x14, 0x1c, 0x1c, 0x1c, 0x1c, 0x1b, 0x1a,
		0x18, 0x13, 0x10, 0x0e, 0x08, 0x07, 0x04, 0x02, 0x00
	};

	switch (sd->sensor) {
	case SENSOR_ADCM1700:
		gamma_base = gamma_spec_0;
		break;
	case SENSOR_HV7131R:
	case SENSOR_MI0360B:
	case SENSOR_MT9V111:
		gamma_base = gamma_spec_1;
		break;
	case SENSOR_GC0307:
		gamma_base = gamma_spec_2;
		break;
	case SENSOR_SP80708:
		gamma_base = gamma_spec_3;
		break;
	default:
		gamma_base = gamma_def;
		break;
	}

	val = sd->ctrls[GAMMA].val;
	for (i = 0; i < sizeof gamma; i++)
		gamma[i] = gamma_base[i]
			+ delta[i] * (val - GAMMA_DEF) / 32;
	reg_w(gspca_dev, 0x20, gamma, sizeof gamma);
}