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
struct xenbus_watch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 size_t XS_WATCH_PATH ; 
 int /*<<< orphan*/  xenbus_dev_changed (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_frontend ; 

__attribute__((used)) static void frontend_changed(struct xenbus_watch *watch,
			     const char **vec, unsigned int len)
{
	DPRINTK("");

	xenbus_dev_changed(vec[XS_WATCH_PATH], &xenbus_frontend);
}