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
struct sd {scalar_t__ snapshot_pressed; } ;
struct gspca_dev {int /*<<< orphan*/  input_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_CAMERA ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  konica_stream_off (struct gspca_dev*) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	konica_stream_off(gspca_dev);
#if defined(CONFIG_INPUT) || defined(CONFIG_INPUT_MODULE)
	/* Don't keep the button in the pressed state "forever" if it was
	   pressed when streaming is stopped */
	if (sd->snapshot_pressed) {
		input_report_key(gspca_dev->input_dev, KEY_CAMERA, 0);
		input_sync(gspca_dev->input_dev);
		sd->snapshot_pressed = 0;
	}
#endif
}