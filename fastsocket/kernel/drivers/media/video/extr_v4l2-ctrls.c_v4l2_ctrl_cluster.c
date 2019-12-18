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
struct v4l2_ctrl {unsigned int ncontrols; struct v4l2_ctrl** cluster; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 

void v4l2_ctrl_cluster(unsigned ncontrols, struct v4l2_ctrl **controls)
{
	int i;

	/* The first control is the master control and it must not be NULL */
	BUG_ON(controls[0] == NULL);

	for (i = 0; i < ncontrols; i++) {
		if (controls[i]) {
			controls[i]->cluster = controls;
			controls[i]->ncontrols = ncontrols;
		}
	}
}