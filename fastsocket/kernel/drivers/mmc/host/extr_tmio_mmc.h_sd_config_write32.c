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
typedef  int u32 ;
struct tmio_mmc_host {int bus_shift; scalar_t__ cnf; } ;

/* Variables and functions */
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static inline void sd_config_write32(struct tmio_mmc_host *host, int addr,
		u32 val)
{
	writew(val, host->cnf + (addr << host->bus_shift));
	writew(val >> 16, host->cnf + ((addr + 2) << host->bus_shift));
}