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
struct psmouse {scalar_t__ model; TYPE_2__ ps2dev; struct hgpk_data* private; } ;
struct hgpk_data {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dattr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dattr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HGPK_MODEL_C ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hgpk_data*) ; 
 TYPE_4__ psmouse_attr_powered ; 
 TYPE_3__ psmouse_attr_recalibrate ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 

__attribute__((used)) static void hgpk_disconnect(struct psmouse *psmouse)
{
	struct hgpk_data *priv = psmouse->private;

	device_remove_file(&psmouse->ps2dev.serio->dev,
			   &psmouse_attr_powered.dattr);

	if (psmouse->model >= HGPK_MODEL_C)
		device_remove_file(&psmouse->ps2dev.serio->dev,
				   &psmouse_attr_recalibrate.dattr);

	psmouse_reset(psmouse);
	kfree(priv);
}