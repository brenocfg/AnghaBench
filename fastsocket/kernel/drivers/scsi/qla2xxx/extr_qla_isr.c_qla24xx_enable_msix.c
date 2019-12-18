#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rsp_que {struct qla_msix_entry* msix; } ;
struct qla_msix_entry {int vector; int entry; int have_irq; struct rsp_que* rsp; } ;
struct TYPE_4__ {int msix_enabled; } ;
struct qla_hw_data {int msix_count; int max_rsp_queues; int mqenable; int max_req_queues; int /*<<< orphan*/  mqiobase; scalar_t__ msixbase; struct qla_msix_entry* msix_entries; TYPE_1__ flags; int /*<<< orphan*/  pdev; } ;
struct msix_entry {int entry; int vector; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA83XX (struct qla_hw_data*) ; 
 int MIN_MSIX_COUNT ; 
 int /*<<< orphan*/  kfree (struct msix_entry*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* msix_entries ; 
 int pci_enable_msix (int /*<<< orphan*/ ,struct msix_entry*,int) ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_dbg_multiq ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_disable_msix (struct qla_hw_data*) ; 
 TYPE_2__* qla82xx_msix_entries ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rsp_que*) ; 

__attribute__((used)) static int
qla24xx_enable_msix(struct qla_hw_data *ha, struct rsp_que *rsp)
{
#define MIN_MSIX_COUNT	2
	int i, ret;
	struct msix_entry *entries;
	struct qla_msix_entry *qentry;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	entries = kzalloc(sizeof(struct msix_entry) * ha->msix_count,
			GFP_KERNEL);
	if (!entries) {
		ql_log(ql_log_warn, vha, 0x00bc,
		    "Failed to allocate memory for msix_entry.\n");
		return -ENOMEM;
	}

	for (i = 0; i < ha->msix_count; i++)
		entries[i].entry = i;

	ret = pci_enable_msix(ha->pdev, entries, ha->msix_count);
	if (ret) {
		if (ret < MIN_MSIX_COUNT)
			goto msix_failed;

		ql_log(ql_log_warn, vha, 0x00c6,
		    "MSI-X: Failed to enable support "
		    "-- %d/%d\n Retry with %d vectors.\n",
		    ha->msix_count, ret, ret);
		ha->msix_count = ret;
		ret = pci_enable_msix(ha->pdev, entries, ha->msix_count);
		if (ret) {
msix_failed:
			ql_log(ql_log_fatal, vha, 0x00c7,
			    "MSI-X: Failed to enable support, "
			    "giving   up -- %d/%d.\n",
			    ha->msix_count, ret);
			goto msix_out;
		}
		ha->max_rsp_queues = ha->msix_count - 1;
	}
	ha->msix_entries = kzalloc(sizeof(struct qla_msix_entry) *
				ha->msix_count, GFP_KERNEL);
	if (!ha->msix_entries) {
		ql_log(ql_log_fatal, vha, 0x00c8,
		    "Failed to allocate memory for ha->msix_entries.\n");
		ret = -ENOMEM;
		goto msix_out;
	}
	ha->flags.msix_enabled = 1;

	for (i = 0; i < ha->msix_count; i++) {
		qentry = &ha->msix_entries[i];
		qentry->vector = entries[i].vector;
		qentry->entry = entries[i].entry;
		qentry->have_irq = 0;
		qentry->rsp = NULL;
	}

	/* Enable MSI-X vectors for the base queue */
	for (i = 0; i < 2; i++) {
		qentry = &ha->msix_entries[i];
		if (IS_QLA82XX(ha)) {
			ret = request_irq(qentry->vector,
				qla82xx_msix_entries[i].handler,
				0, qla82xx_msix_entries[i].name, rsp);
		} else {
			ret = request_irq(qentry->vector,
				msix_entries[i].handler,
				0, msix_entries[i].name, rsp);
		}
		if (ret) {
			ql_log(ql_log_fatal, vha, 0x00cb,
			    "MSI-X: unable to register handler -- %x/%d.\n",
			    qentry->vector, ret);
			qla24xx_disable_msix(ha);
			ha->mqenable = 0;
			goto msix_out;
		}
		qentry->have_irq = 1;
		qentry->rsp = rsp;
		rsp->msix = qentry;
	}

	/* Enable MSI-X vector for response queue update for queue 0 */
	if (IS_QLA83XX(ha)) {
		if (ha->msixbase && ha->mqiobase &&
		    (ha->max_rsp_queues > 1 || ha->max_req_queues > 1))
			ha->mqenable = 1;
	} else
		if (ha->mqiobase
		    && (ha->max_rsp_queues > 1 || ha->max_req_queues > 1))
			ha->mqenable = 1;
	ql_dbg(ql_dbg_multiq, vha, 0xc005,
	    "mqiobase=%p, max_rsp_queues=%d, max_req_queues=%d.\n",
	    ha->mqiobase, ha->max_rsp_queues, ha->max_req_queues);
	ql_dbg(ql_dbg_init, vha, 0x0055,
	    "mqiobase=%p, max_rsp_queues=%d, max_req_queues=%d.\n",
	    ha->mqiobase, ha->max_rsp_queues, ha->max_req_queues);

msix_out:
	kfree(entries);
	return ret;
}