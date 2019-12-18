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
struct zfcp_qdio {int /*<<< orphan*/  req_q_wq; } ;
struct zfcp_erp_action {TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; struct zfcp_qdio* qdio; } ;

/* Variables and functions */
 int ZFCP_ERP_FAILED ; 
 int ZFCP_ERP_SUCCEEDED ; 
 int /*<<< orphan*/  ZFCP_STATUS_ADAPTER_QDIOUP ; 
 int /*<<< orphan*/  atomic_set_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ zfcp_qdio_open (struct zfcp_qdio*) ; 

__attribute__((used)) static int zfcp_erp_adapter_strategy_open_qdio(struct zfcp_erp_action *act)
{
	struct zfcp_qdio *qdio = act->adapter->qdio;

	if (zfcp_qdio_open(qdio))
		return ZFCP_ERP_FAILED;
	init_waitqueue_head(&qdio->req_q_wq);
	atomic_set_mask(ZFCP_STATUS_ADAPTER_QDIOUP, &act->adapter->status);
	return ZFCP_ERP_SUCCEEDED;
}