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
typedef  int u32 ;
struct vm_area_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct ehca_cq {int /*<<< orphan*/  cq_number; TYPE_1__ ib_cq; int /*<<< orphan*/  mm_count_queue; int /*<<< orphan*/  ipz_queue; int /*<<< orphan*/  mm_count_galpa; int /*<<< orphan*/  galpas; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ehca_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int ehca_mmap_fw (struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ehca_mmap_queue (struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int ehca_mmap_cq(struct vm_area_struct *vma, struct ehca_cq *cq,
			u32 rsrc_type)
{
	int ret;

	switch (rsrc_type) {
	case 0: /* galpa fw handle */
		ehca_dbg(cq->ib_cq.device, "cq_num=%x fw", cq->cq_number);
		ret = ehca_mmap_fw(vma, &cq->galpas, &cq->mm_count_galpa);
		if (unlikely(ret)) {
			ehca_err(cq->ib_cq.device,
				 "ehca_mmap_fw() failed rc=%i cq_num=%x",
				 ret, cq->cq_number);
			return ret;
		}
		break;

	case 1: /* cq queue_addr */
		ehca_dbg(cq->ib_cq.device, "cq_num=%x queue", cq->cq_number);
		ret = ehca_mmap_queue(vma, &cq->ipz_queue, &cq->mm_count_queue);
		if (unlikely(ret)) {
			ehca_err(cq->ib_cq.device,
				 "ehca_mmap_queue() failed rc=%i cq_num=%x",
				 ret, cq->cq_number);
			return ret;
		}
		break;

	default:
		ehca_err(cq->ib_cq.device, "bad resource type=%x cq_num=%x",
			 rsrc_type, cq->cq_number);
		return -EINVAL;
	}

	return 0;
}