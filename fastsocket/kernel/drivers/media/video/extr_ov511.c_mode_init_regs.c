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
struct usb_ov511 {scalar_t__ bclass; int sensor; int /*<<< orphan*/  mirror; int /*<<< orphan*/  backlight; scalar_t__ lightfreq; int /*<<< orphan*/  auto_exp; int /*<<< orphan*/  auto_brt; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ FATAL_ERROR (int) ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int /*<<< orphan*/ ) ; 
#define  SEN_KS0127 136 
#define  SEN_KS0127B 135 
#define  SEN_OV6620 134 
#define  SEN_OV6630 133 
#define  SEN_OV7610 132 
#define  SEN_OV7620 131 
#define  SEN_OV76BE 130 
#define  SEN_OV8600 129 
#define  SEN_SAA7111A 128 
 int /*<<< orphan*/  bandingfilter ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  i2c_r (struct usb_ov511*,int) ; 
 int /*<<< orphan*/  lightfreq ; 
 int ov511_mode_init_regs (struct usb_ov511*,int,int,int,int) ; 
 int ov518_mode_init_regs (struct usb_ov511*,int,int,int,int) ; 
 int sensor_set_auto_brightness (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int sensor_set_auto_exposure (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int sensor_set_backlight (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int sensor_set_banding_filter (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int sensor_set_light_freq (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int sensor_set_mirror (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int set_ov_sensor_window (struct usb_ov511*,int,int,int,int) ; 

__attribute__((used)) static int
mode_init_regs(struct usb_ov511 *ov,
	       int width, int height, int mode, int sub_flag)
{
	int rc = 0;

	if (!ov || !ov->dev)
		return -EFAULT;

	if (ov->bclass == BCL_OV518) {
		rc = ov518_mode_init_regs(ov, width, height, mode, sub_flag);
	} else {
		rc = ov511_mode_init_regs(ov, width, height, mode, sub_flag);
	}

	if (FATAL_ERROR(rc))
		return rc;

	switch (ov->sensor) {
	case SEN_OV7610:
	case SEN_OV7620:
	case SEN_OV76BE:
	case SEN_OV8600:
	case SEN_OV6620:
	case SEN_OV6630:
		rc = set_ov_sensor_window(ov, width, height, mode, sub_flag);
		break;
	case SEN_KS0127:
	case SEN_KS0127B:
		err("KS0127-series decoders not supported yet");
		rc = -EINVAL;
		break;
	case SEN_SAA7111A:
//		rc = mode_init_saa_sensor_regs(ov, width, height, mode,
//					       sub_flag);

		PDEBUG(1, "SAA status = 0x%02X", i2c_r(ov, 0x1f));
		break;
	default:
		err("Unknown sensor");
		rc = -EINVAL;
	}

	if (FATAL_ERROR(rc))
		return rc;

	/* Sensor-independent settings */
	rc = sensor_set_auto_brightness(ov, ov->auto_brt);
	if (FATAL_ERROR(rc))
		return rc;

	rc = sensor_set_auto_exposure(ov, ov->auto_exp);
	if (FATAL_ERROR(rc))
		return rc;

	rc = sensor_set_banding_filter(ov, bandingfilter);
	if (FATAL_ERROR(rc))
		return rc;

	if (ov->lightfreq) {
		rc = sensor_set_light_freq(ov, lightfreq);
		if (FATAL_ERROR(rc))
			return rc;
	}

	rc = sensor_set_backlight(ov, ov->backlight);
	if (FATAL_ERROR(rc))
		return rc;

	rc = sensor_set_mirror(ov, ov->mirror);
	if (FATAL_ERROR(rc))
		return rc;

	return 0;
}