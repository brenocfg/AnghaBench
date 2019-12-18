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
struct gameport {struct a3d* port_data; } ;
struct a3d {int* axes; int buttons; } ;

/* Variables and functions */

__attribute__((used)) static int a3d_adc_cooked_read(struct gameport *gameport, int *axes, int *buttons)
{
	struct a3d *a3d = gameport->port_data;
	int i;

	for (i = 0; i < 4; i++)
		axes[i] = (a3d->axes[i] < 254) ? a3d->axes[i] : -1;
	*buttons = a3d->buttons;
	return 0;
}