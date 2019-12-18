#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct serio_driver {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct serio {char* phys; TYPE_2__ dev; scalar_t__ parent; TYPE_1__ id; } ;
struct psmouse {int /*<<< orphan*/  (* disconnect ) (struct psmouse*) ;struct input_dev* dev; int /*<<< orphan*/  (* pt_deactivate ) (struct psmouse*) ;int /*<<< orphan*/  (* pt_activate ) (struct psmouse*) ;int /*<<< orphan*/  smartscroll; int /*<<< orphan*/  resync_time; int /*<<< orphan*/  resetafter; int /*<<< orphan*/  resolution; int /*<<< orphan*/  rate; int /*<<< orphan*/  phys; int /*<<< orphan*/  resync_work; int /*<<< orphan*/  ps2dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSMOUSE_CMD_MODE ; 
 int /*<<< orphan*/  PSMOUSE_IGNORE ; 
 int /*<<< orphan*/  PSMOUSE_INITIALIZING ; 
 scalar_t__ SERIO_PS_PSTHRU ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct psmouse*) ; 
 struct psmouse* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps2_init (int /*<<< orphan*/ *,struct serio*) ; 
 int /*<<< orphan*/  psmouse_activate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_attribute_group ; 
 int /*<<< orphan*/  psmouse_deactivate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_initialize (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_mutex ; 
 scalar_t__ psmouse_probe (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_rate ; 
 int /*<<< orphan*/  psmouse_resetafter ; 
 int /*<<< orphan*/  psmouse_resolution ; 
 int /*<<< orphan*/  psmouse_resync ; 
 int /*<<< orphan*/  psmouse_resync_time ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_smartscroll ; 
 int /*<<< orphan*/  psmouse_switch_protocol (struct psmouse*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct psmouse* serio_get_drvdata (scalar_t__) ; 
 int serio_open (struct serio*,struct serio_driver*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,struct psmouse*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct psmouse*) ; 
 int /*<<< orphan*/  stub2 (struct psmouse*) ; 
 int /*<<< orphan*/  stub3 (struct psmouse*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psmouse_connect(struct serio *serio, struct serio_driver *drv)
{
	struct psmouse *psmouse, *parent = NULL;
	struct input_dev *input_dev;
	int retval = 0, error = -ENOMEM;

	mutex_lock(&psmouse_mutex);

	/*
	 * If this is a pass-through port deactivate parent so the device
	 * connected to this port can be successfully identified
	 */
	if (serio->parent && serio->id.type == SERIO_PS_PSTHRU) {
		parent = serio_get_drvdata(serio->parent);
		psmouse_deactivate(parent);
	}

	psmouse = kzalloc(sizeof(struct psmouse), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!psmouse || !input_dev)
		goto err_free;

	ps2_init(&psmouse->ps2dev, serio);
	INIT_DELAYED_WORK(&psmouse->resync_work, psmouse_resync);
	psmouse->dev = input_dev;
	snprintf(psmouse->phys, sizeof(psmouse->phys), "%s/input0", serio->phys);

	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	serio_set_drvdata(serio, psmouse);

	error = serio_open(serio, drv);
	if (error)
		goto err_clear_drvdata;

	if (psmouse_probe(psmouse) < 0) {
		error = -ENODEV;
		goto err_close_serio;
	}

	psmouse->rate = psmouse_rate;
	psmouse->resolution = psmouse_resolution;
	psmouse->resetafter = psmouse_resetafter;
	psmouse->resync_time = parent ? 0 : psmouse_resync_time;
	psmouse->smartscroll = psmouse_smartscroll;

	psmouse_switch_protocol(psmouse, NULL);

	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);
	psmouse_initialize(psmouse);

	error = input_register_device(psmouse->dev);
	if (error)
		goto err_protocol_disconnect;

	if (parent && parent->pt_activate)
		parent->pt_activate(parent);

	error = sysfs_create_group(&serio->dev.kobj, &psmouse_attribute_group);
	if (error)
		goto err_pt_deactivate;

	psmouse_activate(psmouse);

 out:
	/* If this is a pass-through port the parent needs to be re-activated */
	if (parent)
		psmouse_activate(parent);

	mutex_unlock(&psmouse_mutex);
	return retval;

 err_pt_deactivate:
	if (parent && parent->pt_deactivate)
		parent->pt_deactivate(parent);
	input_unregister_device(psmouse->dev);
	input_dev = NULL; /* so we don't try to free it below */
 err_protocol_disconnect:
	if (psmouse->disconnect)
		psmouse->disconnect(psmouse);
	psmouse_set_state(psmouse, PSMOUSE_IGNORE);
 err_close_serio:
	serio_close(serio);
 err_clear_drvdata:
	serio_set_drvdata(serio, NULL);
 err_free:
	input_free_device(input_dev);
	kfree(psmouse);

	retval = error;
	goto out;
}