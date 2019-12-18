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
struct parisc_driver {int /*<<< orphan*/  (* remove ) (struct parisc_device*) ;} ;
struct parisc_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct parisc_device*) ; 
 struct parisc_device* to_parisc_device (struct device*) ; 
 struct parisc_driver* to_parisc_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parisc_driver_remove(struct device *dev)
{
	struct parisc_device *pa_dev = to_parisc_device(dev);
	struct parisc_driver *pa_drv = to_parisc_driver(dev->driver);
	if (pa_drv->remove)
		pa_drv->remove(pa_dev);

	return 0;
}