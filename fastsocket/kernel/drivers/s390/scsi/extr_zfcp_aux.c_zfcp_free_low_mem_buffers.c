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
struct TYPE_2__ {scalar_t__ gid_pn_data; scalar_t__ status_read_data; scalar_t__ status_read_req; scalar_t__ qtcb_pool; scalar_t__ scsi_abort; scalar_t__ scsi_req; scalar_t__ erp_req; } ;
struct zfcp_adapter {TYPE_1__ pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  mempool_destroy (scalar_t__) ; 

__attribute__((used)) static void zfcp_free_low_mem_buffers(struct zfcp_adapter *adapter)
{
	/* zfcp_data.config_mutex must be held */
	if (adapter->pool.erp_req)
		mempool_destroy(adapter->pool.erp_req);
	if (adapter->pool.scsi_req)
		mempool_destroy(adapter->pool.scsi_req);
	if (adapter->pool.scsi_abort)
		mempool_destroy(adapter->pool.scsi_abort);
	if (adapter->pool.qtcb_pool)
		mempool_destroy(adapter->pool.qtcb_pool);
	if (adapter->pool.status_read_req)
		mempool_destroy(adapter->pool.status_read_req);
	if (adapter->pool.status_read_data)
		mempool_destroy(adapter->pool.status_read_data);
	if (adapter->pool.gid_pn_data)
		mempool_destroy(adapter->pool.gid_pn_data);
}