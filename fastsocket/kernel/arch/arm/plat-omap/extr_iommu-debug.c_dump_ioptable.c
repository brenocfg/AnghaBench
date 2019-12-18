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
struct iommu {int /*<<< orphan*/  page_table_lock; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int IOPGD_SHIFT ; 
 int IOPGD_TABLE ; 
 int IOPTE_SHIFT ; 
 int PTRS_PER_IOPGD ; 
 int PTRS_PER_IOPTE ; 
 int dump_ioptable_entry_one (int,int,int) ; 
 int* iopgd_offset (struct iommu*,int /*<<< orphan*/ ) ; 
 int* iopte_offset (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t dump_ioptable(struct iommu *obj, char *buf, ssize_t len)
{
	int i;
	u32 *iopgd;
	char *p = buf;

	spin_lock(&obj->page_table_lock);

	iopgd = iopgd_offset(obj, 0);
	for (i = 0; i < PTRS_PER_IOPGD; i++, iopgd++) {
		int j, err;
		u32 *iopte;
		u32 da;

		if (!*iopgd)
			continue;

		if (!(*iopgd & IOPGD_TABLE)) {
			da = i << IOPGD_SHIFT;

			err = dump_ioptable_entry_one(1, da, *iopgd);
			if (err)
				goto out;
			continue;
		}

		iopte = iopte_offset(iopgd, 0);

		for (j = 0; j < PTRS_PER_IOPTE; j++, iopte++) {
			if (!*iopte)
				continue;

			da = (i << IOPGD_SHIFT) + (j << IOPTE_SHIFT);
			err = dump_ioptable_entry_one(2, da, *iopgd);
			if (err)
				goto out;
		}
	}
out:
	spin_unlock(&obj->page_table_lock);

	return p - buf;
}