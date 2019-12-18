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
typedef  unsigned long u64 ;
typedef  unsigned int u32 ;
struct ipz_queue {unsigned long qe_size; } ;
struct ehca_queue_map {unsigned int tail; unsigned int next_wqe_idx; int /*<<< orphan*/  entries; int /*<<< orphan*/  left_to_poll; TYPE_1__* map; } ;
struct TYPE_2__ {scalar_t__ cqe_req; } ;

/* Variables and functions */
 int EFAULT ; 
 void* abs_to_virt (unsigned long) ; 
 int /*<<< orphan*/  ehca_gen_err (char*,unsigned long,void*) ; 
 scalar_t__ ipz_queue_abs_to_offset (struct ipz_queue*,unsigned long,unsigned long*) ; 
 unsigned int next_index (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int calc_left_cqes(u64 wqe_p, struct ipz_queue *ipz_queue,
			  struct ehca_queue_map *qmap)
{
	void *wqe_v;
	u64 q_ofs;
	u32 wqe_idx;
	unsigned int tail_idx;

	/* convert real to abs address */
	wqe_p = wqe_p & (~(1UL << 63));

	wqe_v = abs_to_virt(wqe_p);

	if (ipz_queue_abs_to_offset(ipz_queue, wqe_p, &q_ofs)) {
		ehca_gen_err("Invalid offset for calculating left cqes "
				"wqe_p=%#llx wqe_v=%p\n", wqe_p, wqe_v);
		return -EFAULT;
	}

	tail_idx = next_index(qmap->tail, qmap->entries);
	wqe_idx = q_ofs / ipz_queue->qe_size;

	/* check all processed wqes, whether a cqe is requested or not */
	while (tail_idx != wqe_idx) {
		if (qmap->map[tail_idx].cqe_req)
			qmap->left_to_poll++;
		tail_idx = next_index(tail_idx, qmap->entries);
	}
	/* save index in queue, where we have to start flushing */
	qmap->next_wqe_idx = wqe_idx;
	return 0;
}