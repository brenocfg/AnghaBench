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
struct TYPE_4__ {scalar_t__ bmdma_addr; } ;
struct TYPE_3__ {struct ata_device* device; } ;
struct ata_port {TYPE_2__ ioaddr; struct ata_device* private_data; TYPE_1__ link; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_sff_dev_select (struct ata_port*,unsigned int) ; 
 int /*<<< orphan*/  iowrite8 (int,scalar_t__) ; 
 int /*<<< orphan*/  ninja32_set_piomode (struct ata_port*,struct ata_device*) ; 

__attribute__((used)) static void ninja32_dev_select(struct ata_port *ap, unsigned int device)
{
	struct ata_device *adev = &ap->link.device[device];
	if (ap->private_data != adev) {
		iowrite8(0xd6, ap->ioaddr.bmdma_addr + 0x1f);
		ata_sff_dev_select(ap, device);
		ninja32_set_piomode(ap, adev);
	}
}