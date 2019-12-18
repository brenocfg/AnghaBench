#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ vaddr; scalar_t__ msix_vector; scalar_t__ msi_vector; } ;
typedef  TYPE_1__ ctlr_info_t ;

/* Variables and functions */
 scalar_t__ SA5_INTR_STATUS ; 
 scalar_t__ SA5_OUTDB_STATUS ; 
 unsigned long SA5_OUTDB_STATUS_PERF_BIT ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long SA5_performant_intr_pending(ctlr_info_t *h)
{
	unsigned long register_value = readl(h->vaddr + SA5_INTR_STATUS);

	if (!register_value)
		return 0;

	if (h->msi_vector || h->msix_vector)
		return 1;

	/* Read outbound doorbell to flush */
	register_value = readl(h->vaddr + SA5_OUTDB_STATUS);
	return register_value & SA5_OUTDB_STATUS_PERF_BIT;
}