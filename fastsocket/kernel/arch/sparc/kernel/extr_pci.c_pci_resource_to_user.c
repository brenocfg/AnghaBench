#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; scalar_t__ end; scalar_t__ start; } ;
struct TYPE_8__ {unsigned long start; } ;
struct TYPE_7__ {unsigned long start; } ;
struct pci_pbm_info {TYPE_4__ mem_space; TYPE_3__ io_space; } ;
struct TYPE_5__ {struct pci_pbm_info* host_controller; } ;
struct TYPE_6__ {TYPE_1__ archdata; } ;
struct pci_dev {TYPE_2__ dev; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int IORESOURCE_IO ; 

void pci_resource_to_user(const struct pci_dev *pdev, int bar,
			  const struct resource *rp, resource_size_t *start,
			  resource_size_t *end)
{
	struct pci_pbm_info *pbm = pdev->dev.archdata.host_controller;
	unsigned long offset;

	if (rp->flags & IORESOURCE_IO)
		offset = pbm->io_space.start;
	else
		offset = pbm->mem_space.start;

	*start = rp->start - offset;
	*end = rp->end - offset;
}