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
struct pps_device {TYPE_1__* dev; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pps_class ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

void pps_unregister_cdev(struct pps_device *pps)
{
	pr_debug("unregistering pps%d\n", pps->id);
	device_destroy(pps_class, pps->dev->devt);
}