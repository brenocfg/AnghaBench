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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int (* sleep_wake ) (struct pci_dev*,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* pci_platform_pm ; 
 int stub1 (struct pci_dev*,int) ; 

__attribute__((used)) static inline int platform_pci_sleep_wake(struct pci_dev *dev, bool enable)
{
	return pci_platform_pm ?
			pci_platform_pm->sleep_wake(dev, enable) : -ENODEV;
}