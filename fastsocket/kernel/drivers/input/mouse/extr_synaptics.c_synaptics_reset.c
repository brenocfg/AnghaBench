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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  synaptics_mode_cmd (struct psmouse*,int /*<<< orphan*/ ) ; 

void synaptics_reset(struct psmouse *psmouse)
{
	/* reset touchpad back to relative mode, gestures enabled */
	synaptics_mode_cmd(psmouse, 0);
}