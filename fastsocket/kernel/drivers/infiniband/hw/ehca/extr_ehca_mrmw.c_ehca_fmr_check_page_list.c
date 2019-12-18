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
typedef  int u64 ;
typedef  int u32 ;
struct ehca_mr {int fmr_max_pages; int fmr_page_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int,int,...) ; 

int ehca_fmr_check_page_list(struct ehca_mr *e_fmr,
			     u64 *page_list,
			     int list_len)
{
	u32 i;
	u64 *page;

	if ((list_len == 0) || (list_len > e_fmr->fmr_max_pages)) {
		ehca_gen_err("bad list_len, list_len=%x "
			     "e_fmr->fmr_max_pages=%x fmr=%p",
			     list_len, e_fmr->fmr_max_pages, e_fmr);
		return -EINVAL;
	}

	/* each page must be aligned */
	page = page_list;
	for (i = 0; i < list_len; i++) {
		if (*page % e_fmr->fmr_page_size) {
			ehca_gen_err("bad page, i=%x *page=%llx page=%p fmr=%p "
				     "fmr_page_size=%x", i, *page, page, e_fmr,
				     e_fmr->fmr_page_size);
			return -EINVAL;
		}
		page++;
	}

	return 0;
}