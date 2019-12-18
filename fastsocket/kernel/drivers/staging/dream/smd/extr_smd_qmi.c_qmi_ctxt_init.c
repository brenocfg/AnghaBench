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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct qmi_ctxt {int ctl_txn_id; int wds_txn_id; int wds_busy; int /*<<< orphan*/  state; TYPE_1__ misc; int /*<<< orphan*/  wake_lock; int /*<<< orphan*/  open_work; int /*<<< orphan*/  read_work; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_OFFLINE ; 
 int /*<<< orphan*/  WAKE_LOCK_SUSPEND ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_open_work ; 
 int /*<<< orphan*/  qmi_read_work ; 
 int /*<<< orphan*/  wake_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qmi_ctxt_init(struct qmi_ctxt *ctxt, unsigned n)
{
	mutex_init(&ctxt->lock);
	INIT_WORK(&ctxt->read_work, qmi_read_work);
	INIT_WORK(&ctxt->open_work, qmi_open_work);
	wake_lock_init(&ctxt->wake_lock, WAKE_LOCK_SUSPEND, ctxt->misc.name);
	ctxt->ctl_txn_id = 1;
	ctxt->wds_txn_id = 1;
	ctxt->wds_busy = 1;
	ctxt->state = STATE_OFFLINE;

}