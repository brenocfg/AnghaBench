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
struct trackpoint_data {int press_to_select; int skipback; int ext_dev; int /*<<< orphan*/  jenks; int /*<<< orphan*/  ztime; int /*<<< orphan*/  upthresh; int /*<<< orphan*/  thresh; int /*<<< orphan*/  mindrag; int /*<<< orphan*/  draghys; int /*<<< orphan*/  reach; int /*<<< orphan*/  speed; int /*<<< orphan*/  inertia; int /*<<< orphan*/  sensitivity; } ;
struct psmouse {int /*<<< orphan*/  ps2dev; struct trackpoint_data* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_DRAGHYS ; 
 int /*<<< orphan*/  TP_INERTIA ; 
 int /*<<< orphan*/  TP_JENKS_CURV ; 
 unsigned char TP_MASK_EXT_DEV ; 
 unsigned char TP_MASK_MB ; 
 unsigned char TP_MASK_PTSON ; 
 unsigned char TP_MASK_SKIPBACK ; 
 unsigned char TP_MASK_SOURCE_TAG ; 
 unsigned char TP_MASK_TWOHAND ; 
 int /*<<< orphan*/  TP_MINDRAG ; 
 int /*<<< orphan*/  TP_REACH ; 
 int /*<<< orphan*/  TP_SENS ; 
 int /*<<< orphan*/  TP_SPEED ; 
 int /*<<< orphan*/  TP_THRESH ; 
 int /*<<< orphan*/  TP_TOGGLE_EXT_DEV ; 
 int /*<<< orphan*/  TP_TOGGLE_MB ; 
 int /*<<< orphan*/  TP_TOGGLE_PTSON ; 
 int /*<<< orphan*/  TP_TOGGLE_SKIPBACK ; 
 int /*<<< orphan*/  TP_TOGGLE_SOURCE_TAG ; 
 int /*<<< orphan*/  TP_TOGGLE_TWOHAND ; 
 int /*<<< orphan*/  TP_UP_THRESH ; 
 int /*<<< orphan*/  TP_Z_TIME ; 
 int /*<<< orphan*/  trackpoint_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  trackpoint_toggle_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  trackpoint_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trackpoint_sync(struct psmouse *psmouse)
{
	struct trackpoint_data *tp = psmouse->private;
	unsigned char toggle;

	/* Disable features that may make device unusable with this driver */
	trackpoint_read(&psmouse->ps2dev, TP_TOGGLE_TWOHAND, &toggle);
	if (toggle & TP_MASK_TWOHAND)
		trackpoint_toggle_bit(&psmouse->ps2dev, TP_TOGGLE_TWOHAND, TP_MASK_TWOHAND);

	trackpoint_read(&psmouse->ps2dev, TP_TOGGLE_SOURCE_TAG, &toggle);
	if (toggle & TP_MASK_SOURCE_TAG)
		trackpoint_toggle_bit(&psmouse->ps2dev, TP_TOGGLE_SOURCE_TAG, TP_MASK_SOURCE_TAG);

	trackpoint_read(&psmouse->ps2dev, TP_TOGGLE_MB, &toggle);
	if (toggle & TP_MASK_MB)
		trackpoint_toggle_bit(&psmouse->ps2dev, TP_TOGGLE_MB, TP_MASK_MB);

	/* Push the config to the device */
	trackpoint_write(&psmouse->ps2dev, TP_SENS, tp->sensitivity);
	trackpoint_write(&psmouse->ps2dev, TP_INERTIA, tp->inertia);
	trackpoint_write(&psmouse->ps2dev, TP_SPEED, tp->speed);

	trackpoint_write(&psmouse->ps2dev, TP_REACH, tp->reach);
	trackpoint_write(&psmouse->ps2dev, TP_DRAGHYS, tp->draghys);
	trackpoint_write(&psmouse->ps2dev, TP_MINDRAG, tp->mindrag);

	trackpoint_write(&psmouse->ps2dev, TP_THRESH, tp->thresh);
	trackpoint_write(&psmouse->ps2dev, TP_UP_THRESH, tp->upthresh);

	trackpoint_write(&psmouse->ps2dev, TP_Z_TIME, tp->ztime);
	trackpoint_write(&psmouse->ps2dev, TP_JENKS_CURV, tp->jenks);

	trackpoint_read(&psmouse->ps2dev, TP_TOGGLE_PTSON, &toggle);
	if (((toggle & TP_MASK_PTSON) == TP_MASK_PTSON) != tp->press_to_select)
		 trackpoint_toggle_bit(&psmouse->ps2dev, TP_TOGGLE_PTSON, TP_MASK_PTSON);

	trackpoint_read(&psmouse->ps2dev, TP_TOGGLE_SKIPBACK, &toggle);
	if (((toggle & TP_MASK_SKIPBACK) == TP_MASK_SKIPBACK) != tp->skipback)
		trackpoint_toggle_bit(&psmouse->ps2dev, TP_TOGGLE_SKIPBACK, TP_MASK_SKIPBACK);

	trackpoint_read(&psmouse->ps2dev, TP_TOGGLE_EXT_DEV, &toggle);
	if (((toggle & TP_MASK_EXT_DEV) == TP_MASK_EXT_DEV) != tp->ext_dev)
		trackpoint_toggle_bit(&psmouse->ps2dev, TP_TOGGLE_EXT_DEV, TP_MASK_EXT_DEV);

	return 0;
}