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
struct zfcp_qdio {int /*<<< orphan*/  req_q_full; struct zfcp_adapter* adapter; int /*<<< orphan*/  req_q_lock; int /*<<< orphan*/  req_q_wq; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 int ZFCP_STATUS_ADAPTER_QDIOUP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 long wait_event_interruptible_lock_bh_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fsf_sbal_check (struct zfcp_qdio*) ; 

__attribute__((used)) static int zfcp_fsf_req_sbal_get(struct zfcp_qdio *qdio)
{
	struct zfcp_adapter *adapter = qdio->adapter;
	long ret;

	ret = wait_event_interruptible_lock_bh_timeout(qdio->req_q_wq,
		       zfcp_fsf_sbal_check(qdio), qdio->req_q_lock, 5 * HZ);

	if (!(atomic_read(&qdio->adapter->status) & ZFCP_STATUS_ADAPTER_QDIOUP))
		return -EIO;

	if (ret > 0)
		return 0;

	if (!ret) {
		atomic_inc(&qdio->req_q_full);
		/* assume hanging outbound queue, try queue recovery */
		zfcp_erp_adapter_reopen(adapter, 0, "fsrsg_1", NULL);
	}

	return -EIO;
}