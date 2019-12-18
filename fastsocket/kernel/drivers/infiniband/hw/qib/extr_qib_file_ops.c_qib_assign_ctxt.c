#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qib_user_info {int spu_userversion; unsigned int spu_port_alg; scalar_t__ spu_subctxt_cnt; } ;
struct qib_filedata {int rec_cpu_num; int /*<<< orphan*/  pq; int /*<<< orphan*/  subctxt; struct qib_ctxtdata* rcd; } ;
struct qib_devdata {int flags; TYPE_3__* pcidev; int /*<<< orphan*/  unit; } ;
struct qib_ctxtdata {int /*<<< orphan*/  ctxt; struct qib_devdata* dd; } ;
struct file {struct qib_filedata* private_data; TYPE_1__* f_dentry; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int QIB_HAS_SEND_DMA ; 
 unsigned int QIB_PORT_ALG_ACROSS ; 
 unsigned int QIB_PORT_ALG_COUNT ; 
 int QIB_USER_MINOR_BASE ; 
 unsigned int QIB_USER_SWMAJOR ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ ) ; 
 unsigned int cpumask_weight (int /*<<< orphan*/ ) ; 
 scalar_t__ ctxt_fp (struct file*) ; 
 TYPE_2__* current ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int find_free_ctxt (int,struct file*,struct qib_user_info const*) ; 
 int find_shared_ctxt (struct file*,struct qib_user_info const*) ; 
 int get_a_ctxt (struct file*,struct qib_user_info const*,unsigned int) ; 
 int iminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ qib_compatible_subctxts (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  qib_cpulist ; 
 unsigned int qib_cpulist_count ; 
 int /*<<< orphan*/  qib_devinfo (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_mutex ; 
 int /*<<< orphan*/  qib_user_sdma_queue_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsk_cpus_allowed (TYPE_2__*) ; 

__attribute__((used)) static int qib_assign_ctxt(struct file *fp, const struct qib_user_info *uinfo)
{
	int ret;
	int i_minor;
	unsigned swmajor, swminor, alg = QIB_PORT_ALG_ACROSS;

	/* Check to be sure we haven't already initialized this file */
	if (ctxt_fp(fp)) {
		ret = -EINVAL;
		goto done;
	}

	/* for now, if major version is different, bail */
	swmajor = uinfo->spu_userversion >> 16;
	if (swmajor != QIB_USER_SWMAJOR) {
		ret = -ENODEV;
		goto done;
	}

	swminor = uinfo->spu_userversion & 0xffff;

	if (swminor >= 11 && uinfo->spu_port_alg < QIB_PORT_ALG_COUNT)
		alg = uinfo->spu_port_alg;

	mutex_lock(&qib_mutex);

	if (qib_compatible_subctxts(swmajor, swminor) &&
	    uinfo->spu_subctxt_cnt) {
		ret = find_shared_ctxt(fp, uinfo);
		if (ret) {
			if (ret > 0)
				ret = 0;
			goto done_chk_sdma;
		}
	}

	i_minor = iminor(fp->f_dentry->d_inode) - QIB_USER_MINOR_BASE;
	if (i_minor)
		ret = find_free_ctxt(i_minor - 1, fp, uinfo);
	else
		ret = get_a_ctxt(fp, uinfo, alg);

done_chk_sdma:
	if (!ret) {
		struct qib_filedata *fd = fp->private_data;
		const struct qib_ctxtdata *rcd = fd->rcd;
		const struct qib_devdata *dd = rcd->dd;
		unsigned int weight;

		if (dd->flags & QIB_HAS_SEND_DMA) {
			fd->pq = qib_user_sdma_queue_create(&dd->pcidev->dev,
							    dd->unit,
							    rcd->ctxt,
							    fd->subctxt);
			if (!fd->pq)
				ret = -ENOMEM;
		}

		/*
		 * If process has NOT already set it's affinity, select and
		 * reserve a processor for it, as a rendezvous for all
		 * users of the driver.  If they don't actually later
		 * set affinity to this cpu, or set it to some other cpu,
		 * it just means that sooner or later we don't recommend
		 * a cpu, and let the scheduler do it's best.
		 */
		weight = cpumask_weight(tsk_cpus_allowed(current));
		if (!ret && weight >= qib_cpulist_count) {
			int cpu;
			cpu = find_first_zero_bit(qib_cpulist,
						  qib_cpulist_count);
			if (cpu != qib_cpulist_count) {
				__set_bit(cpu, qib_cpulist);
				fd->rec_cpu_num = cpu;
			}
		} else if (weight == 1 &&
			test_bit(cpumask_first(tsk_cpus_allowed(current)),
				 qib_cpulist))
			qib_devinfo(dd->pcidev,
				"%s PID %u affinity set to cpu %d; already allocated\n",
				current->comm, current->pid,
				cpumask_first(tsk_cpus_allowed(current)));
	}

	mutex_unlock(&qib_mutex);

done:
	return ret;
}