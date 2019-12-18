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
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct serio {struct serio* parent; TYPE_2__ id; TYPE_1__ dev; } ;
struct psmouse {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* pt_deactivate ) (struct psmouse*) ;int /*<<< orphan*/  (* disconnect ) (struct psmouse*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PSMOUSE_CMD_MODE ; 
 int /*<<< orphan*/  PSMOUSE_IGNORE ; 
 scalar_t__ SERIO_PS_PSTHRU ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct psmouse*) ; 
 int /*<<< orphan*/  kpsmoused_wq ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psmouse_activate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_attribute_group ; 
 int /*<<< orphan*/  psmouse_deactivate (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_mutex ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_close (struct serio*) ; 
 struct psmouse* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  serio_set_drvdata (struct serio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct psmouse*) ; 
 int /*<<< orphan*/  stub2 (struct psmouse*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psmouse_disconnect(struct serio *serio)
{
	struct psmouse *psmouse, *parent = NULL;

	psmouse = serio_get_drvdata(serio);

	sysfs_remove_group(&serio->dev.kobj, &psmouse_attribute_group);

	mutex_lock(&psmouse_mutex);

	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

	/* make sure we don't have a resync in progress */
	mutex_unlock(&psmouse_mutex);
	flush_workqueue(kpsmoused_wq);
	mutex_lock(&psmouse_mutex);

	if (serio->parent && serio->id.type == SERIO_PS_PSTHRU) {
		parent = serio_get_drvdata(serio->parent);
		psmouse_deactivate(parent);
	}

	if (psmouse->disconnect)
		psmouse->disconnect(psmouse);

	if (parent && parent->pt_deactivate)
		parent->pt_deactivate(parent);

	psmouse_set_state(psmouse, PSMOUSE_IGNORE);

	serio_close(serio);
	serio_set_drvdata(serio, NULL);
	input_unregister_device(psmouse->dev);
	kfree(psmouse);

	if (parent)
		psmouse_activate(parent);

	mutex_unlock(&psmouse_mutex);
}