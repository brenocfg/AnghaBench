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
struct TYPE_4__ {int /*<<< orphan*/  data_addr; } ;
struct ata_port {TYPE_2__ ioaddr; } ;
struct ata_device {TYPE_1__* link; } ;
struct TYPE_3__ {struct ata_port* ap; } ;

/* Variables and functions */
 int READ ; 
 int /*<<< orphan*/  ioread8_rep (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  iowrite8_rep (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 

__attribute__((used)) static unsigned int ata_data_xfer_8bit(struct ata_device *dev,
				unsigned char *buf, unsigned int buflen, int rw)
{
	struct ata_port *ap = dev->link->ap;

	if (rw == READ)
		ioread8_rep(ap->ioaddr.data_addr, buf, buflen);
	else
		iowrite8_rep(ap->ioaddr.data_addr, buf, buflen);

	return buflen;
}