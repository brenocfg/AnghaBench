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
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_host {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esdhc_writel(struct sdhci_host *host, u32 val, int reg)
{
	out_be32(host->ioaddr + reg, val);
}