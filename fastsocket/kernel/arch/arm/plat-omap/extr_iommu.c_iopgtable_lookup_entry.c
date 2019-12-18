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
struct iommu {int dummy; } ;

/* Variables and functions */
 int IOPGD_TABLE ; 
 int* iopgd_offset (struct iommu*,int) ; 
 int* iopte_offset (int*,int) ; 

void iopgtable_lookup_entry(struct iommu *obj, u32 da, u32 **ppgd, u32 **ppte)
{
	u32 *iopgd, *iopte = NULL;

	iopgd = iopgd_offset(obj, da);
	if (!*iopgd)
		goto out;

	if (*iopgd & IOPGD_TABLE)
		iopte = iopte_offset(iopgd, da);
out:
	*ppgd = iopgd;
	*ppte = iopte;
}