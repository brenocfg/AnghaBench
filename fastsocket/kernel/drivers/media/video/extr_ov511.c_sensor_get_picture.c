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
struct video_picture {int whiteness; int /*<<< orphan*/  hue; int /*<<< orphan*/  colour; int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; } ;
struct usb_ov511 {int dummy; } ;

/* Variables and functions */
 scalar_t__ FATAL_ERROR (int) ; 
 int /*<<< orphan*/  PDEBUG (int,char*) ; 
 int sensor_get_brightness (struct usb_ov511*,int /*<<< orphan*/ *) ; 
 int sensor_get_contrast (struct usb_ov511*,int /*<<< orphan*/ *) ; 
 int sensor_get_hue (struct usb_ov511*,int /*<<< orphan*/ *) ; 
 int sensor_get_saturation (struct usb_ov511*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sensor_get_picture(struct usb_ov511 *ov, struct video_picture *p)
{
	int rc;

	PDEBUG(4, "sensor_get_picture");

	/* Don't return error if a setting is unsupported, or rest of settings
	 * will not be performed */

	rc = sensor_get_contrast(ov, &(p->contrast));
	if (FATAL_ERROR(rc))
		return rc;

	rc = sensor_get_brightness(ov, &(p->brightness));
	if (FATAL_ERROR(rc))
		return rc;

	rc = sensor_get_saturation(ov, &(p->colour));
	if (FATAL_ERROR(rc))
		return rc;

	rc = sensor_get_hue(ov, &(p->hue));
	if (FATAL_ERROR(rc))
		return rc;

	p->whiteness = 105 << 8;

	return 0;
}