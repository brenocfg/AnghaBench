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
 int IOLARGE_MASK ; 
 size_t IOPGD_SIZE ; 
 int IOPGD_SUPER ; 
 int IOPGD_TABLE ; 
 int IOPTE_LARGE ; 
 size_t IOPTE_SIZE ; 
 int IOSUPER_MASK ; 
 int PTRS_PER_IOPTE ; 
 int /*<<< orphan*/  flush_iopgd_range (int*,int*) ; 
 int /*<<< orphan*/  flush_iopte_range (int*,int*) ; 
 int* iopgd_offset (struct iommu*,int) ; 
 int /*<<< orphan*/  iopte_free (int*) ; 
 int* iopte_offset (int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t iopgtable_clear_entry_core(struct iommu *obj, u32 da)
{
	size_t bytes;
	u32 *iopgd = iopgd_offset(obj, da);
	int nent = 1;

	if (!*iopgd)
		return 0;

	if (*iopgd & IOPGD_TABLE) {
		int i;
		u32 *iopte = iopte_offset(iopgd, da);

		bytes = IOPTE_SIZE;
		if (*iopte & IOPTE_LARGE) {
			nent *= 16;
			/* rewind to the 1st entry */
			iopte = (u32 *)((u32)iopte & IOLARGE_MASK);
		}
		bytes *= nent;
		memset(iopte, 0, nent * sizeof(*iopte));
		flush_iopte_range(iopte, iopte + (nent - 1) * sizeof(*iopte));

		/*
		 * do table walk to check if this table is necessary or not
		 */
		iopte = iopte_offset(iopgd, 0);
		for (i = 0; i < PTRS_PER_IOPTE; i++)
			if (iopte[i])
				goto out;

		iopte_free(iopte);
		nent = 1; /* for the next L1 entry */
	} else {
		bytes = IOPGD_SIZE;
		if ((*iopgd & IOPGD_SUPER) == IOPGD_SUPER) {
			nent *= 16;
			/* rewind to the 1st entry */
			iopgd = (u32 *)((u32)iopgd & IOSUPER_MASK);
		}
		bytes *= nent;
	}
	memset(iopgd, 0, nent * sizeof(*iopgd));
	flush_iopgd_range(iopgd, iopgd + (nent - 1) * sizeof(*iopgd));
out:
	return bytes;
}