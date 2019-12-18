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
struct TYPE_2__ {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  device; } ;
struct ehca_qp {TYPE_1__ ib_qp; int /*<<< orphan*/  mm_count_squeue; int /*<<< orphan*/  ipz_squeue; int /*<<< orphan*/  mm_count_rqueue; int /*<<< orphan*/  ipz_rqueue; int /*<<< orphan*/  mm_count_galpa; int /*<<< orphan*/  galpas; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ehca_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int ehca_mmap_fw (struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ehca_mmap_queue (struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int ehca_mmap_qp(struct vm_area_struct *vma, struct ehca_qp *qp,
			u32 rsrc_type)
{
	int ret;

	switch (rsrc_type) {
	case 0: /* galpa fw handle */
		ehca_dbg(qp->ib_qp.device, "qp_num=%x fw", qp->ib_qp.qp_num);
		ret = ehca_mmap_fw(vma, &qp->galpas, &qp->mm_count_galpa);
		if (unlikely(ret)) {
			ehca_err(qp->ib_qp.device,
				 "remap_pfn_range() failed ret=%i qp_num=%x",
				 ret, qp->ib_qp.qp_num);
			return -ENOMEM;
		}
		break;

	case 1: /* qp rqueue_addr */
		ehca_dbg(qp->ib_qp.device, "qp_num=%x rq", qp->ib_qp.qp_num);
		ret = ehca_mmap_queue(vma, &qp->ipz_rqueue,
				      &qp->mm_count_rqueue);
		if (unlikely(ret)) {
			ehca_err(qp->ib_qp.device,
				 "ehca_mmap_queue(rq) failed rc=%i qp_num=%x",
				 ret, qp->ib_qp.qp_num);
			return ret;
		}
		break;

	case 2: /* qp squeue_addr */
		ehca_dbg(qp->ib_qp.device, "qp_num=%x sq", qp->ib_qp.qp_num);
		ret = ehca_mmap_queue(vma, &qp->ipz_squeue,
				      &qp->mm_count_squeue);
		if (unlikely(ret)) {
			ehca_err(qp->ib_qp.device,
				 "ehca_mmap_queue(sq) failed rc=%i qp_num=%x",
				 ret, qp->ib_qp.qp_num);
			return ret;
		}
		break;

	default:
		ehca_err(qp->ib_qp.device, "bad resource type=%x qp=num=%x",
			 rsrc_type, qp->ib_qp.qp_num);
		return -EINVAL;
	}

	return 0;
}