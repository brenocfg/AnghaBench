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
typedef  int u64 ;
struct TYPE_2__ {int max_pages; int page_shift; scalar_t__ max_maps; } ;
struct mthca_fmr {scalar_t__ maps; TYPE_1__ attr; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static inline int mthca_check_fmr(struct mthca_fmr *fmr, u64 *page_list,
				  int list_len, u64 iova)
{
	int i, page_mask;

	if (list_len > fmr->attr.max_pages)
		return -EINVAL;

	page_mask = (1 << fmr->attr.page_shift) - 1;

	/* We are getting page lists, so va must be page aligned. */
	if (iova & page_mask)
		return -EINVAL;

	/* Trust the user not to pass misaligned data in page_list */
	if (0)
		for (i = 0; i < list_len; ++i) {
			if (page_list[i] & ~page_mask)
				return -EINVAL;
		}

	if (fmr->maps >= fmr->attr.max_maps)
		return -EINVAL;

	return 0;
}