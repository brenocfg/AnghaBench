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
struct qlcnic_adapter {TYPE_1__* recv_ctx; } ;
struct TYPE_2__ {int context_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  qlcnic_pf_set_interface_id_ipaddr (struct qlcnic_adapter*,int*) ; 
 scalar_t__ qlcnic_sriov_pf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static void qlcnic_83xx_set_interface_id_ipaddr(struct qlcnic_adapter *adapter,
						u32 *interface_id)
{
	if (qlcnic_sriov_pf_check(adapter)) {
		qlcnic_pf_set_interface_id_ipaddr(adapter, interface_id);
	} else {
		if (!qlcnic_sriov_vf_check(adapter))
			*interface_id = adapter->recv_ctx->context_id << 16;
	}
}