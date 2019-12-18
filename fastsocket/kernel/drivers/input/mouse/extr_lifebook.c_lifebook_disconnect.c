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
struct psmouse {struct lifebook_data* private; } ;
struct lifebook_data {int /*<<< orphan*/  dev2; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct lifebook_data*) ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 

__attribute__((used)) static void lifebook_disconnect(struct psmouse *psmouse)
{
	struct lifebook_data *priv = psmouse->private;

	psmouse_reset(psmouse);
	if (priv) {
		input_unregister_device(priv->dev2);
		kfree(priv);
	}
	psmouse->private = NULL;
}