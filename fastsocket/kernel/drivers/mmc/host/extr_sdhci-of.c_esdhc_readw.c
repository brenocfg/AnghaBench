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
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int SDHCI_HOST_VERSION ; 
 int /*<<< orphan*/  in_be16 (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 esdhc_readw(struct sdhci_host *host, int reg)
{
	u16 ret;

	if (unlikely(reg == SDHCI_HOST_VERSION))
		ret = in_be16(host->ioaddr + reg);
	else
		ret = in_be16(host->ioaddr + (reg ^ 0x2));
	return ret;
}