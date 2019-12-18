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
struct ata_link {struct ata_port* ap; } ;
struct ata_port {struct ata_link* slave_link; struct ata_link link; } ;
struct ata_device {int /*<<< orphan*/  devno; struct ata_link* link; } ;

/* Variables and functions */

struct ata_link *ata_dev_phys_link(struct ata_device *dev)
{
	struct ata_port *ap = dev->link->ap;

	if (!ap->slave_link)
		return dev->link;
	if (!dev->devno)
		return &ap->link;
	return ap->slave_link;
}