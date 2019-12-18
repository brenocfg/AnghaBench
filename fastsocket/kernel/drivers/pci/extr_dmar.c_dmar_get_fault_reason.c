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
typedef  int u8 ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int DMA_REMAP ; 
 int INTR_REMAP ; 
 int UNKNOWN ; 
 char const** dma_remap_fault_reasons ; 
 char const** intr_remap_fault_reasons ; 

const char *dmar_get_fault_reason(u8 fault_reason, int *fault_type)
{
	if (fault_reason >= 0x20 && (fault_reason <= 0x20 +
				     ARRAY_SIZE(intr_remap_fault_reasons))) {
		*fault_type = INTR_REMAP;
		return intr_remap_fault_reasons[fault_reason - 0x20];
	} else if (fault_reason < ARRAY_SIZE(dma_remap_fault_reasons)) {
		*fault_type = DMA_REMAP;
		return dma_remap_fault_reasons[fault_reason];
	} else {
		*fault_type = UNKNOWN;
		return "Unknown";
	}
}