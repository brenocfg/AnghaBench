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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {TYPE_1__* nic_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* request_reset ) (struct qlcnic_adapter*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qlcnic_dev_request_reset(struct qlcnic_adapter *adapter,
					    u32 key)
{
	if (adapter->nic_ops->request_reset)
		adapter->nic_ops->request_reset(adapter, key);
}