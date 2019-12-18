#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int* page_list; int next_listelem; int fmr_pgsize; } ;
struct TYPE_4__ {TYPE_1__ fmr; } ;
struct ehca_mr_pginfo {int hwpage_size; int next_hwpage; TYPE_2__ u; scalar_t__ kpage_cnt; int /*<<< orphan*/  hwpage_cnt; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int,...) ; 
 int phys_to_abs (int) ; 

__attribute__((used)) static int ehca_set_pagebuf_fmr(struct ehca_mr_pginfo *pginfo,
				u32 number, u64 *kpage)
{
	int ret = 0;
	u64 *fmrlist;
	u32 i;

	/* loop over desired page_list entries */
	fmrlist = pginfo->u.fmr.page_list + pginfo->u.fmr.next_listelem;
	for (i = 0; i < number; i++) {
		*kpage = phys_to_abs((*fmrlist & ~(pginfo->hwpage_size - 1)) +
				     pginfo->next_hwpage * pginfo->hwpage_size);
		if ( !(*kpage) ) {
			ehca_gen_err("*fmrlist=%llx fmrlist=%p "
				     "next_listelem=%llx next_hwpage=%llx",
				     *fmrlist, fmrlist,
				     pginfo->u.fmr.next_listelem,
				     pginfo->next_hwpage);
			return -EFAULT;
		}
		(pginfo->hwpage_cnt)++;
		if (pginfo->u.fmr.fmr_pgsize >= pginfo->hwpage_size) {
			if (pginfo->next_hwpage %
			    (pginfo->u.fmr.fmr_pgsize /
			     pginfo->hwpage_size) == 0) {
				(pginfo->kpage_cnt)++;
				(pginfo->u.fmr.next_listelem)++;
				fmrlist++;
				pginfo->next_hwpage = 0;
			} else
				(pginfo->next_hwpage)++;
		} else {
			unsigned int cnt_per_hwpage = pginfo->hwpage_size /
				pginfo->u.fmr.fmr_pgsize;
			unsigned int j;
			u64 prev = *kpage;
			/* check if adrs are contiguous */
			for (j = 1; j < cnt_per_hwpage; j++) {
				u64 p = phys_to_abs(fmrlist[j] &
						    ~(pginfo->hwpage_size - 1));
				if (prev + pginfo->u.fmr.fmr_pgsize != p) {
					ehca_gen_err("uncontiguous fmr pages "
						     "found prev=%llx p=%llx "
						     "idx=%x", prev, p, i + j);
					return -EINVAL;
				}
				prev = p;
			}
			pginfo->kpage_cnt += cnt_per_hwpage;
			pginfo->u.fmr.next_listelem += cnt_per_hwpage;
			fmrlist += cnt_per_hwpage;
		}
		kpage++;
	}
	return ret;
}