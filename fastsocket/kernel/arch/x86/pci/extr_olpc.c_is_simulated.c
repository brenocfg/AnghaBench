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

/* Variables and functions */
 scalar_t__ NB_SLOT ; 
 scalar_t__ PCI_SLOT (unsigned int) ; 
 scalar_t__ SB_SLOT ; 

__attribute__((used)) static int is_simulated(unsigned int bus, unsigned int devfn)
{
	return (!bus && ((PCI_SLOT(devfn) == NB_SLOT) ||
			(PCI_SLOT(devfn) == SB_SLOT)));
}