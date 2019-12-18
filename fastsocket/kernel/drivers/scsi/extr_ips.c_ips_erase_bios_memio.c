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
struct TYPE_5__ {TYPE_1__* pcidev; scalar_t__ mem_ptr; } ;
typedef  TYPE_2__ ips_ha_t ;
struct TYPE_4__ {scalar_t__ revision; } ;

/* Variables and functions */
 scalar_t__ IPS_REG_FLAP ; 
 scalar_t__ IPS_REG_FLDP ; 
 scalar_t__ IPS_REVID_TROMBONE64 ; 
 int /*<<< orphan*/  MDELAY (int) ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ips_erase_bios_memio(ips_ha_t * ha)
{
	int timeout;
	uint8_t status;

	METHOD_TRACE("ips_erase_bios_memio", 1);

	status = 0;

	/* Clear the status register */
	writel(0, ha->mem_ptr + IPS_REG_FLAP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	writeb(0x50, ha->mem_ptr + IPS_REG_FLDP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* Erase Setup */
	writeb(0x20, ha->mem_ptr + IPS_REG_FLDP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* Erase Confirm */
	writeb(0xD0, ha->mem_ptr + IPS_REG_FLDP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* Erase Status */
	writeb(0x70, ha->mem_ptr + IPS_REG_FLDP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	timeout = 80000;	/* 80 seconds */

	while (timeout > 0) {
		if (ha->pcidev->revision == IPS_REVID_TROMBONE64) {
			writel(0, ha->mem_ptr + IPS_REG_FLAP);
			udelay(25);	/* 25 us */
		}

		status = readb(ha->mem_ptr + IPS_REG_FLDP);

		if (status & 0x80)
			break;

		MDELAY(1);
		timeout--;
	}

	/* check for timeout */
	if (timeout <= 0) {
		/* timeout */

		/* try to suspend the erase */
		writeb(0xB0, ha->mem_ptr + IPS_REG_FLDP);
		if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
			udelay(25);	/* 25 us */

		/* wait for 10 seconds */
		timeout = 10000;
		while (timeout > 0) {
			if (ha->pcidev->revision == IPS_REVID_TROMBONE64) {
				writel(0, ha->mem_ptr + IPS_REG_FLAP);
				udelay(25);	/* 25 us */
			}

			status = readb(ha->mem_ptr + IPS_REG_FLDP);

			if (status & 0xC0)
				break;

			MDELAY(1);
			timeout--;
		}

		return (1);
	}

	/* check for valid VPP */
	if (status & 0x08)
		/* VPP failure */
		return (1);

	/* check for successful flash */
	if (status & 0x30)
		/* sequence error */
		return (1);

	/* Otherwise, we were successful */
	/* clear status */
	writeb(0x50, ha->mem_ptr + IPS_REG_FLDP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	/* enable reads */
	writeb(0xFF, ha->mem_ptr + IPS_REG_FLDP);
	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		udelay(25);	/* 25 us */

	return (0);
}