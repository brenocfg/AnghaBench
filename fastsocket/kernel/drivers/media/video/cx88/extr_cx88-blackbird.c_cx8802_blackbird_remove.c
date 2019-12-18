#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cx8802_driver {TYPE_1__* core; } ;
struct TYPE_2__ {int /*<<< orphan*/  dvbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  blackbird_unregister_video (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx8802_blackbird_remove(struct cx8802_driver *drv)
{
	/* blackbird */
	blackbird_unregister_video(drv->core->dvbdev);

	return 0;
}