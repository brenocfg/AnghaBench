#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_1__* pcidev; scalar_t__ io_addr; } ;
typedef  TYPE_2__ ips_ha_t ;
struct TYPE_4__ {scalar_t__ revision; } ;

/* Variables and functions */
 scalar_t__ IPS_REG_FLAP ; 
 scalar_t__ IPS_REG_FLDP ; 
 scalar_t__ IPS_REVID_TROMBONE64 ; 
 int /*<<< orphan*/  MDELAY (int) ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
ips_program_bios(ips_ha_t * ha, char *buffer, uint32_t buffersize,
		 uint32_t offset)
{
	int i;
	int timeout;
	uint8_t status = 0;

	METHOD_TRACE("ips_program_bios", 1);

	status = 0;

	for (i = 0; i < buffersize; i++) {
		/* write a byte */
		outl(i + offset, ha->io_addr + IPS_REG_FLAP);
		if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		outb(0x40, ha->io_addr + IPS_REG_FLDP);
		if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		outb(buffer[i], ha->io_addr + IPS_REG_FLDP);
		if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		/* wait up to one second */
		timeout = 1000;
		while (timeout > 0) {
			if (ha->pcidev->revision == IPS_REVID_TROMBONE64) {
				outl(0, ha->io_addr + IPS_REG_FLAP);
				udelay(25);	/* 25 us */
			}

			status = inb(ha->io_addr + IPS_REG_FLDP);

			if (status & 0x80)
				break;

			MDELAY(1);
			timeout--;
		}

		if (timeout == 0) {
			/* timeout error */
			outl(0, ha->io_addr + IPS_REG_FLAP);
			if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			outb(0xFF, ha->io_addr + IPS_REG_FLDP);
			if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			return (1);
		}

		/* check the status */
		if (status & 0x18) {
			/* programming error */
			outl(0, ha->io_addr + IPS_REG_FLAP);
			if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			outb(0xFF, ha->io_addr + IPS_REG_FLDP);
			if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
				udelay(25);	/* 25 us */

			return (1);
		}
	}			/* end for */

	/* Enable reading */
	outl(0, ha->io_addr + IPS_REG_FLAP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	outb(0xFF, ha->io_addr + IPS_REG_FLDP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	return (0);
}