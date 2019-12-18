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
typedef  int /*<<< orphan*/  u32 ;
struct qib_user_info {unsigned int spu_subctxt_cnt; int spu_userversion; int /*<<< orphan*/  spu_subctxt_id; } ;
struct qib_devdata {int rcvhdrcnt; int rcvhdrentsize; int /*<<< orphan*/  pcidev; } ;
struct qib_ctxtdata {unsigned int rcvegrbuf_chunks; unsigned int rcvegrbuf_size; unsigned int subctxt_cnt; int active_slaves; int redirect_seq_cnt; int /*<<< orphan*/ * subctxt_uregbase; int /*<<< orphan*/ * subctxt_rcvhdr_base; int /*<<< orphan*/  flag; int /*<<< orphan*/  subctxt_id; void* subctxt_rcvegrbuf; } ;

/* Variables and functions */
 unsigned int ALIGN (int,unsigned int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  QIB_CTXT_MASTER_UNINIT ; 
 int /*<<< orphan*/  QIB_USER_SWMAJOR ; 
 int /*<<< orphan*/  QIB_USER_SWMINOR ; 
 unsigned int QLOGIC_IB_MAX_SUBCTXT ; 
 int /*<<< orphan*/  qib_compatible_subctxts (int,int) ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 void* vmalloc_user (unsigned int) ; 

__attribute__((used)) static int init_subctxts(struct qib_devdata *dd,
			 struct qib_ctxtdata *rcd,
			 const struct qib_user_info *uinfo)
{
	int ret = 0;
	unsigned num_subctxts;
	size_t size;

	/*
	 * If the user is requesting zero subctxts,
	 * skip the subctxt allocation.
	 */
	if (uinfo->spu_subctxt_cnt <= 0)
		goto bail;
	num_subctxts = uinfo->spu_subctxt_cnt;

	/* Check for subctxt compatibility */
	if (!qib_compatible_subctxts(uinfo->spu_userversion >> 16,
		uinfo->spu_userversion & 0xffff)) {
		qib_devinfo(dd->pcidev,
			 "Mismatched user version (%d.%d) and driver "
			 "version (%d.%d) while context sharing. Ensure "
			 "that driver and library are from the same "
			 "release.\n",
			 (int) (uinfo->spu_userversion >> 16),
			 (int) (uinfo->spu_userversion & 0xffff),
			 QIB_USER_SWMAJOR, QIB_USER_SWMINOR);
		goto bail;
	}
	if (num_subctxts > QLOGIC_IB_MAX_SUBCTXT) {
		ret = -EINVAL;
		goto bail;
	}

	rcd->subctxt_uregbase = vmalloc_user(PAGE_SIZE * num_subctxts);
	if (!rcd->subctxt_uregbase) {
		ret = -ENOMEM;
		goto bail;
	}
	/* Note: rcd->rcvhdrq_size isn't initialized yet. */
	size = ALIGN(dd->rcvhdrcnt * dd->rcvhdrentsize *
		     sizeof(u32), PAGE_SIZE) * num_subctxts;
	rcd->subctxt_rcvhdr_base = vmalloc_user(size);
	if (!rcd->subctxt_rcvhdr_base) {
		ret = -ENOMEM;
		goto bail_ureg;
	}

	rcd->subctxt_rcvegrbuf = vmalloc_user(rcd->rcvegrbuf_chunks *
					      rcd->rcvegrbuf_size *
					      num_subctxts);
	if (!rcd->subctxt_rcvegrbuf) {
		ret = -ENOMEM;
		goto bail_rhdr;
	}

	rcd->subctxt_cnt = uinfo->spu_subctxt_cnt;
	rcd->subctxt_id = uinfo->spu_subctxt_id;
	rcd->active_slaves = 1;
	rcd->redirect_seq_cnt = 1;
	set_bit(QIB_CTXT_MASTER_UNINIT, &rcd->flag);
	goto bail;

bail_rhdr:
	vfree(rcd->subctxt_rcvhdr_base);
bail_ureg:
	vfree(rcd->subctxt_uregbase);
	rcd->subctxt_uregbase = NULL;
bail:
	return ret;
}