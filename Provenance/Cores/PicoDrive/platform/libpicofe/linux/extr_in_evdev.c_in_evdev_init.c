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
struct in_pdata {int /*<<< orphan*/  defbinds; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  in_evdev_drv ; 
 int /*<<< orphan*/  in_register_driver (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct in_pdata const*) ; 
 int /*<<< orphan*/  stderr ; 

int in_evdev_init(const struct in_pdata *pdata)
{
	if (!pdata) {
		fprintf(stderr, "in_sdl: Missing input platform data\n");
		return -1;
	}

	in_register_driver(&in_evdev_drv, pdata->defbinds, pdata);
	return 0;
}