#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * name; int /*<<< orphan*/ * binds; scalar_t__ probed; int /*<<< orphan*/  drv_id; } ;
typedef  TYPE_1__ in_dev_t ;

/* Variables and functions */
 int IN_MAX_DEVS ; 
 TYPE_1__* in_devices ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 

void in_debug_dump(void)
{
	int i;

	lprintf("# drv probed binds name\n");
	for (i = 0; i < IN_MAX_DEVS; i++) {
		in_dev_t *d = &in_devices[i];
		if (!d->probed && d->name == NULL && d->binds == NULL)
			continue;
		lprintf("%d %3d %6c %5c %s\n", i, d->drv_id, d->probed ? 'y' : 'n',
			d->binds ? 'y' : 'n', d->name);
	}
}