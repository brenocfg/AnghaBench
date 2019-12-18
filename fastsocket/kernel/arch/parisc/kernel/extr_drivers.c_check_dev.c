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
struct TYPE_2__ {scalar_t__ hw_type; } ;
struct parisc_device {TYPE_1__ id; } ;
struct device {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 scalar_t__ HPHW_FAULTY ; 
 int /*<<< orphan*/  parisc_bus_type ; 
 struct parisc_device* to_parisc_device (struct device*) ; 

__attribute__((used)) static inline int check_dev(struct device *dev)
{
	if (dev->bus == &parisc_bus_type) {
		struct parisc_device *pdev;
		pdev = to_parisc_device(dev);
		return pdev->id.hw_type != HPHW_FAULTY;
	}
	return 1;
}