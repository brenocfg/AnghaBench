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
struct qib_user_sdma_queue {int dummy; } ;
struct qib_filedata {struct qib_user_sdma_queue* pq; } ;
struct qib_ctxtdata {int dummy; } ;
struct kiocb {TYPE_1__* ki_filp; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct qib_filedata* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct qib_ctxtdata* ctxt_fp (TYPE_1__*) ; 
 int /*<<< orphan*/  qib_user_sdma_writev (struct qib_ctxtdata*,struct qib_user_sdma_queue*,struct iovec const*,unsigned long) ; 

__attribute__((used)) static ssize_t qib_aio_write(struct kiocb *iocb, const struct iovec *iov,
			     unsigned long dim, loff_t off)
{
	struct qib_filedata *fp = iocb->ki_filp->private_data;
	struct qib_ctxtdata *rcd = ctxt_fp(iocb->ki_filp);
	struct qib_user_sdma_queue *pq = fp->pq;

	if (!dim || !pq)
		return -EINVAL;

	return qib_user_sdma_writev(rcd, pq, iov, dim);
}