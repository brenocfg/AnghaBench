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
struct sdhci_of_host {int clock; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 struct sdhci_of_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static unsigned int esdhc_get_min_clock(struct sdhci_host *host)
{
	struct sdhci_of_host *of_host = sdhci_priv(host);

	return of_host->clock / 256 / 16;
}