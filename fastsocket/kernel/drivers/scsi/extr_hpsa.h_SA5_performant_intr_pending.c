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
struct ctlr_info {scalar_t__ vaddr; scalar_t__ msix_vector; scalar_t__ msi_vector; } ;

/* Variables and functions */
 scalar_t__ SA5_INTR_STATUS ; 
 scalar_t__ SA5_OUTDB_STATUS ; 
 unsigned long SA5_OUTDB_STATUS_PERF_BIT ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static bool SA5_performant_intr_pending(struct ctlr_info *h)
{
	unsigned long register_value = readl(h->vaddr + SA5_INTR_STATUS);

	if (!register_value)
		return false;

	if (h->msi_vector || h->msix_vector)
		return true;

	/* Read outbound doorbell to flush */
	register_value = readl(h->vaddr + SA5_OUTDB_STATUS);
	return register_value & SA5_OUTDB_STATUS_PERF_BIT;
}