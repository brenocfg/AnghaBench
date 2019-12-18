#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* serio; } ;
struct psmouse {int pktsize; int resetafter; scalar_t__ model; TYPE_2__ ps2dev; scalar_t__ resync_time; int /*<<< orphan*/  reconnect; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  poll; int /*<<< orphan*/  protocol_handler; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  keybit; int /*<<< orphan*/  relbit; int /*<<< orphan*/  evbit; } ;
struct TYPE_8__ {int /*<<< orphan*/  dattr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dattr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
 scalar_t__ HGPK_MODEL_C ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hgpk_disconnect ; 
 int /*<<< orphan*/  hgpk_err (struct psmouse*,char*) ; 
 int /*<<< orphan*/  hgpk_poll ; 
 int /*<<< orphan*/  hgpk_process_byte ; 
 int /*<<< orphan*/  hgpk_reconnect ; 
 TYPE_4__ psmouse_attr_powered ; 
 TYPE_3__ psmouse_attr_recalibrate ; 

__attribute__((used)) static int hgpk_register(struct psmouse *psmouse)
{
	struct input_dev *dev = psmouse->dev;
	int err;

	/* unset the things that psmouse-base sets which we don't have */
	__clear_bit(BTN_MIDDLE, dev->keybit);

	/* set the things we do have */
	__set_bit(EV_KEY, dev->evbit);
	__set_bit(EV_REL, dev->evbit);

	__set_bit(REL_X, dev->relbit);
	__set_bit(REL_Y, dev->relbit);

	__set_bit(BTN_LEFT, dev->keybit);
	__set_bit(BTN_RIGHT, dev->keybit);

	/* register handlers */
	psmouse->protocol_handler = hgpk_process_byte;
	psmouse->poll = hgpk_poll;
	psmouse->disconnect = hgpk_disconnect;
	psmouse->reconnect = hgpk_reconnect;
	psmouse->pktsize = 3;

	/* Disable the idle resync. */
	psmouse->resync_time = 0;
	/* Reset after a lot of bad bytes. */
	psmouse->resetafter = 1024;

	err = device_create_file(&psmouse->ps2dev.serio->dev,
				 &psmouse_attr_powered.dattr);
	if (err) {
		hgpk_err(psmouse, "Failed creating 'powered' sysfs node\n");
		return err;
	}

	/* C-series touchpads added the recalibrate command */
	if (psmouse->model >= HGPK_MODEL_C) {
		err = device_create_file(&psmouse->ps2dev.serio->dev,
					 &psmouse_attr_recalibrate.dattr);
		if (err) {
			hgpk_err(psmouse,
				"Failed creating 'recalibrate' sysfs node\n");
			device_remove_file(&psmouse->ps2dev.serio->dev,
					&psmouse_attr_powered.dattr);
			return err;
		}
	}

	return 0;
}