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
struct ql3_adapter {int /*<<< orphan*/ * shadow_reg_virt_addr; int /*<<< orphan*/  shadow_reg_phy_addr; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_free_buffer_queues (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_free_large_buffers (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_free_net_req_rsp_queues (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_free_send_free_list (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_free_small_buffers (struct ql3_adapter*) ; 

__attribute__((used)) static void ql_free_mem_resources(struct ql3_adapter *qdev)
{
	ql_free_send_free_list(qdev);
	ql_free_large_buffers(qdev);
	ql_free_small_buffers(qdev);
	ql_free_buffer_queues(qdev);
	ql_free_net_req_rsp_queues(qdev);
	if (qdev->shadow_reg_virt_addr != NULL) {
		pci_free_consistent(qdev->pdev,
				    PAGE_SIZE,
				    qdev->shadow_reg_virt_addr,
				    qdev->shadow_reg_phy_addr);
		qdev->shadow_reg_virt_addr = NULL;
	}
}