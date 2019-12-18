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
typedef  int u8 ;
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int ESDHC_HOST_CONTROL_RES ; 
 int SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  clrsetbits_be32 (scalar_t__,int,int) ; 

__attribute__((used)) static void esdhc_writeb(struct sdhci_host *host, u8 val, int reg)
{
	int base = reg & ~0x3;
	int shift = (reg & 0x3) * 8;

	/* Prevent SDHCI core from writing reserved bits (e.g. HISPD). */
	if (reg == SDHCI_HOST_CONTROL)
		val &= ~ESDHC_HOST_CONTROL_RES;

	clrsetbits_be32(host->ioaddr + base , 0xff << shift, val << shift);
}