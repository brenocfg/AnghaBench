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
struct consw {int dummy; } ;
struct con_driver {int flag; scalar_t__ last; scalar_t__ first; scalar_t__ node; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * desc; struct consw const* con; } ;

/* Variables and functions */
 int CON_DRIVER_FLAG_MODULE ; 
 int ENODEV ; 
 int MAX_NR_CON_DRIVER ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 scalar_t__ con_is_bound (struct consw const*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct con_driver* registered_con_driver ; 
 int /*<<< orphan*/  release_console_sem () ; 
 int /*<<< orphan*/  vtconsole_class ; 
 int /*<<< orphan*/  vtconsole_deinit_device (struct con_driver*) ; 

int unregister_con_driver(const struct consw *csw)
{
	int i, retval = -ENODEV;

	acquire_console_sem();

	/* cannot unregister a bound driver */
	if (con_is_bound(csw))
		goto err;

	for (i = 0; i < MAX_NR_CON_DRIVER; i++) {
		struct con_driver *con_driver = &registered_con_driver[i];

		if (con_driver->con == csw &&
		    con_driver->flag & CON_DRIVER_FLAG_MODULE) {
			vtconsole_deinit_device(con_driver);
			device_destroy(vtconsole_class,
				       MKDEV(0, con_driver->node));
			con_driver->con = NULL;
			con_driver->desc = NULL;
			con_driver->dev = NULL;
			con_driver->node = 0;
			con_driver->flag = 0;
			con_driver->first = 0;
			con_driver->last = 0;
			retval = 0;
			break;
		}
	}
err:
	release_console_sem();
	return retval;
}