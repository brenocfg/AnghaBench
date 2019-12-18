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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  device_addr; } ;
struct ata_port {TYPE_1__ ioaddr; } ;

/* Variables and functions */
 int ATA_DEV1 ; 
 int ATA_DEVICE_OBS ; 
 int /*<<< orphan*/  ata_sff_pause (struct ata_port*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void scc_dev_select (struct ata_port *ap, unsigned int device)
{
	u8 tmp;

	if (device == 0)
		tmp = ATA_DEVICE_OBS;
	else
		tmp = ATA_DEVICE_OBS | ATA_DEV1;

	out_be32(ap->ioaddr.device_addr, tmp);
	ata_sff_pause(ap);
}