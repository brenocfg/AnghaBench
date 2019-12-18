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
struct atmel_mci {int bus_hz; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int ns_to_clocks(struct atmel_mci *host,
					unsigned int ns)
{
	return (ns * (host->bus_hz / 1000000) + 999) / 1000;
}