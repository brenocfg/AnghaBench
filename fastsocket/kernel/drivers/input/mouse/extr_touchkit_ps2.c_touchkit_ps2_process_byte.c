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
struct psmouse {unsigned char* packet; int pktcnt; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  PSMOUSE_FULL_PACKET ; 
 int /*<<< orphan*/  PSMOUSE_GOOD_DATA ; 
 int /*<<< orphan*/  TOUCHKIT_GET_TOUCHED (unsigned char*) ; 
 int /*<<< orphan*/  TOUCHKIT_GET_X (unsigned char*) ; 
 int /*<<< orphan*/  TOUCHKIT_GET_Y (unsigned char*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static psmouse_ret_t touchkit_ps2_process_byte(struct psmouse *psmouse)
{
	unsigned char *packet = psmouse->packet;
	struct input_dev *dev = psmouse->dev;

	if (psmouse->pktcnt != 5)
		return PSMOUSE_GOOD_DATA;

	input_report_abs(dev, ABS_X, TOUCHKIT_GET_X(packet));
	input_report_abs(dev, ABS_Y, TOUCHKIT_GET_Y(packet));
	input_report_key(dev, BTN_TOUCH, TOUCHKIT_GET_TOUCHED(packet));
	input_sync(dev);

	return PSMOUSE_FULL_PACKET;
}