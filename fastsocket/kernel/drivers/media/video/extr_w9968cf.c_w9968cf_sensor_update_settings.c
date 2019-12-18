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
struct w9968cf_device {int /*<<< orphan*/  mirror; int /*<<< orphan*/  backlight; int /*<<< orphan*/  lightfreq; int /*<<< orphan*/  bandfilt; int /*<<< orphan*/  auto_exp; int /*<<< orphan*/  auto_brt; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVCAMCHIP_CID_AUTOBRIGHT ; 
 int /*<<< orphan*/  OVCAMCHIP_CID_AUTOEXP ; 
 int /*<<< orphan*/  OVCAMCHIP_CID_BACKLIGHT ; 
 int /*<<< orphan*/  OVCAMCHIP_CID_BANDFILT ; 
 int /*<<< orphan*/  OVCAMCHIP_CID_FREQ ; 
 int /*<<< orphan*/  OVCAMCHIP_CID_MIRROR ; 
 int w9968cf_sensor_set_control (struct w9968cf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w9968cf_sensor_update_settings(struct w9968cf_device* cam)
{
	int err = 0;

	/* Auto brightness */
	err = w9968cf_sensor_set_control(cam, OVCAMCHIP_CID_AUTOBRIGHT,
					 cam->auto_brt);
	if (err)
		return err;

	/* Auto exposure */
	err = w9968cf_sensor_set_control(cam, OVCAMCHIP_CID_AUTOEXP,
					 cam->auto_exp);
	if (err)
		return err;

	/* Banding filter */
	err = w9968cf_sensor_set_control(cam, OVCAMCHIP_CID_BANDFILT,
					 cam->bandfilt);
	if (err)
		return err;

	/* Light frequency */
	err = w9968cf_sensor_set_control(cam, OVCAMCHIP_CID_FREQ,
					 cam->lightfreq);
	if (err)
		return err;

	/* Back light */
	err = w9968cf_sensor_set_control(cam, OVCAMCHIP_CID_BACKLIGHT,
					 cam->backlight);
	if (err)
		return err;

	/* Mirror */
	err = w9968cf_sensor_set_control(cam, OVCAMCHIP_CID_MIRROR,
					 cam->mirror);
	if (err)
		return err;

	return 0;
}