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
struct TYPE_2__ {int /*<<< orphan*/  present; } ;
struct sd {scalar_t__ bridge; scalar_t__ snapshot_pressed; TYPE_1__ gspca_dev; } ;
struct gspca_dev {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_OV519 ; 
 scalar_t__ BRIDGE_W9968CF ; 
 int /*<<< orphan*/  KEY_CAMERA ; 
 int /*<<< orphan*/  OV519_R57_SNAPSHOT ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w9968cf_stop0 (struct sd*) ; 

__attribute__((used)) static void sd_stop0(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (!sd->gspca_dev.present)
		return;
	if (sd->bridge == BRIDGE_W9968CF)
		w9968cf_stop0(sd);

#if defined(CONFIG_INPUT) || defined(CONFIG_INPUT_MODULE)
	/* If the last button state is pressed, release it now! */
	if (sd->snapshot_pressed) {
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
		sd->snapshot_pressed = 0;
	}
#endif
	if (sd->bridge == BRIDGE_OV519)
		reg_w(sd, OV519_R57_SNAPSHOT, 0x23);
}