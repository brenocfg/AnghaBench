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
struct TYPE_2__ {int pci_suscfg; unsigned int off_duration; unsigned int on_duration; } ;

/* Variables and functions */
 int SUSMOD ; 
 TYPE_1__* gx_params ; 
 unsigned int stock_freq ; 

__attribute__((used)) static unsigned int gx_get_cpuspeed(unsigned int cpu)
{
	if ((gx_params->pci_suscfg & SUSMOD) == 0)
		return stock_freq;

	return (stock_freq * gx_params->off_duration)
		/ (gx_params->on_duration + gx_params->off_duration);
}