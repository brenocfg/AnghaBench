#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct pci_dev {int devfn; TYPE_2__* sriov; TYPE_1__* bus; } ;
struct TYPE_4__ {int offset; int stride; } ;
struct TYPE_3__ {scalar_t__ number; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 virtfn_bus(struct pci_dev *dev, int id)
{
	return dev->bus->number + ((dev->devfn + dev->sriov->offset +
				    dev->sriov->stride * id) >> 8);
}