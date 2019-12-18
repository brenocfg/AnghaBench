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
struct intel_uncore_box {scalar_t__ pci_dev; } ;

/* Variables and functions */
 int uncore_msr_fixed_ctr (struct intel_uncore_box*) ; 
 int uncore_pci_fixed_ctr (struct intel_uncore_box*) ; 

__attribute__((used)) static inline
unsigned uncore_fixed_ctr(struct intel_uncore_box *box)
{
	if (box->pci_dev)
		return uncore_pci_fixed_ctr(box);
	else
		return uncore_msr_fixed_ctr(box);
}