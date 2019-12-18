#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
typedef  int u32 ;
struct ipath_lkey_table {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int max_segs; int length; TYPE_2__** map; void* iova; void* user_base; } ;
struct ipath_fmr {int page_shift; TYPE_3__ mr; } ;
struct ib_fmr {int /*<<< orphan*/  device; } ;
struct TYPE_8__ {struct ipath_lkey_table lk_table; } ;
struct TYPE_6__ {TYPE_1__* segs; } ;
struct TYPE_5__ {int length; void* vaddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int IPATH_SEGSZ ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_4__* to_idev (int /*<<< orphan*/ ) ; 
 struct ipath_fmr* to_ifmr (struct ib_fmr*) ; 

int ipath_map_phys_fmr(struct ib_fmr *ibfmr, u64 * page_list,
		       int list_len, u64 iova)
{
	struct ipath_fmr *fmr = to_ifmr(ibfmr);
	struct ipath_lkey_table *rkt;
	unsigned long flags;
	int m, n, i;
	u32 ps;
	int ret;

	if (list_len > fmr->mr.max_segs) {
		ret = -EINVAL;
		goto bail;
	}
	rkt = &to_idev(ibfmr->device)->lk_table;
	spin_lock_irqsave(&rkt->lock, flags);
	fmr->mr.user_base = iova;
	fmr->mr.iova = iova;
	ps = 1 << fmr->page_shift;
	fmr->mr.length = list_len * ps;
	m = 0;
	n = 0;
	ps = 1 << fmr->page_shift;
	for (i = 0; i < list_len; i++) {
		fmr->mr.map[m]->segs[n].vaddr = (void *) page_list[i];
		fmr->mr.map[m]->segs[n].length = ps;
		if (++n == IPATH_SEGSZ) {
			m++;
			n = 0;
		}
	}
	spin_unlock_irqrestore(&rkt->lock, flags);
	ret = 0;

bail:
	return ret;
}