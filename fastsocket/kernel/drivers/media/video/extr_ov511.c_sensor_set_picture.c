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
struct video_picture {int /*<<< orphan*/  hue; int /*<<< orphan*/  colour; int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  whiteness; } ;
struct usb_ov511 {int /*<<< orphan*/  whiteness; } ;

/* Variables and functions */
 scalar_t__ FATAL_ERROR (int) ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int sensor_set_brightness (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int sensor_set_contrast (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int sensor_set_hue (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int sensor_set_saturation (struct usb_ov511*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sensor_set_picture(struct usb_ov511 *ov, struct video_picture *p)
{
	int rc;

	PDEBUG(4, "sensor_set_picture");

	ov->whiteness = p->whiteness;

	/* Don't return error if a setting is unsupported, or rest of settings
	 * will not be performed */

	rc = sensor_set_contrast(ov, p->contrast);
	if (FATAL_ERROR(rc))
		return rc;

	rc = sensor_set_brightness(ov, p->brightness);
	if (FATAL_ERROR(rc))
		return rc;

	rc = sensor_set_saturation(ov, p->colour);
	if (FATAL_ERROR(rc))
		return rc;

	rc = sensor_set_hue(ov, p->hue);
	if (FATAL_ERROR(rc))
		return rc;

	return 0;
}