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
struct ib_phys_buf {int addr; scalar_t__ size; } ;
struct TYPE_3__ {int next_buf; struct ib_phys_buf* phys_buf_array; } ;
struct TYPE_4__ {TYPE_1__ phy; } ;
struct ehca_mr_pginfo {int hwpage_size; int next_hwpage; scalar_t__ kpage_cnt; scalar_t__ num_kpages; scalar_t__ hwpage_cnt; scalar_t__ num_hwpages; TYPE_2__ u; } ;

/* Variables and functions */
 int EFAULT ; 
 int NUM_CHUNKS (scalar_t__,int) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int,scalar_t__,int,...) ; 
 int phys_to_abs (int) ; 

__attribute__((used)) static int ehca_set_pagebuf_phys(struct ehca_mr_pginfo *pginfo,
				 u32 number, u64 *kpage)
{
	int ret = 0;
	struct ib_phys_buf *pbuf;
	u64 num_hw, offs_hw;
	u32 i = 0;

	/* loop over desired phys_buf_array entries */
	while (i < number) {
		pbuf   = pginfo->u.phy.phys_buf_array + pginfo->u.phy.next_buf;
		num_hw  = NUM_CHUNKS((pbuf->addr % pginfo->hwpage_size) +
				     pbuf->size, pginfo->hwpage_size);
		offs_hw = (pbuf->addr & ~(pginfo->hwpage_size - 1)) /
			pginfo->hwpage_size;
		while (pginfo->next_hwpage < offs_hw + num_hw) {
			/* sanity check */
			if ((pginfo->kpage_cnt >= pginfo->num_kpages) ||
			    (pginfo->hwpage_cnt >= pginfo->num_hwpages)) {
				ehca_gen_err("kpage_cnt >= num_kpages, "
					     "kpage_cnt=%llx num_kpages=%llx "
					     "hwpage_cnt=%llx "
					     "num_hwpages=%llx i=%x",
					     pginfo->kpage_cnt,
					     pginfo->num_kpages,
					     pginfo->hwpage_cnt,
					     pginfo->num_hwpages, i);
				return -EFAULT;
			}
			*kpage = phys_to_abs(
				(pbuf->addr & ~(pginfo->hwpage_size - 1)) +
				(pginfo->next_hwpage * pginfo->hwpage_size));
			if ( !(*kpage) && pbuf->addr ) {
				ehca_gen_err("pbuf->addr=%llx pbuf->size=%llx "
					     "next_hwpage=%llx", pbuf->addr,
					     pbuf->size, pginfo->next_hwpage);
				return -EFAULT;
			}
			(pginfo->hwpage_cnt)++;
			(pginfo->next_hwpage)++;
			if (PAGE_SIZE >= pginfo->hwpage_size) {
				if (pginfo->next_hwpage %
				    (PAGE_SIZE / pginfo->hwpage_size) == 0)
					(pginfo->kpage_cnt)++;
			} else
				pginfo->kpage_cnt += pginfo->hwpage_size /
					PAGE_SIZE;
			kpage++;
			i++;
			if (i >= number) break;
		}
		if (pginfo->next_hwpage >= offs_hw + num_hw) {
			(pginfo->u.phy.next_buf)++;
			pginfo->next_hwpage = 0;
		}
	}
	return ret;
}