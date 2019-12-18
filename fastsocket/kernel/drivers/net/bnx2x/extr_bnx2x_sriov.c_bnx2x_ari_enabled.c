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
struct pci_dev {TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* self; } ;
struct TYPE_3__ {scalar_t__ ari_enabled; } ;

/* Variables and functions */

__attribute__((used)) static int bnx2x_ari_enabled(struct pci_dev *dev)
{
	return dev->bus->self && dev->bus->self->ari_enabled;
}