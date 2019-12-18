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
typedef  scalar_t__ u8 ;
struct sd {scalar_t__ snapshot_pressed; int snapshot_needs_reset; int bridge; } ;
struct gspca_dev {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
#define  BRIDGE_OV511 130 
#define  BRIDGE_OV511PLUS 129 
#define  BRIDGE_OV519 128 
 int /*<<< orphan*/  KEY_CAMERA ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov51x_handle_button(struct gspca_dev *gspca_dev, u8 state)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->snapshot_pressed != state) {
#if defined(CONFIG_INPUT) || defined(CONFIG_INPUT_MODULE)
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, state);
		input_sync(gspca_dev->input_dev);
#endif
		if (state)
			sd->snapshot_needs_reset = 1;

		sd->snapshot_pressed = state;
	} else {
		/* On the ov511 / ov519 we need to reset the button state
		   multiple times, as resetting does not work as long as the
		   button stays pressed */
		switch (sd->bridge) {
		case BRIDGE_OV511:
		case BRIDGE_OV511PLUS:
		case BRIDGE_OV519:
			if (state)
				sd->snapshot_needs_reset = 1;
			break;
		}
	}
}