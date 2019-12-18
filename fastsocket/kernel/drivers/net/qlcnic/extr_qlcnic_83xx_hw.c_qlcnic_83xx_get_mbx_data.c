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
struct TYPE_2__ {int num; int /*<<< orphan*/ * arg; } ;
struct qlcnic_cmd_args {TYPE_1__ rsp; } ;
struct qlcnic_adapter {int /*<<< orphan*/  ahw; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_MBX_FW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qlcnic_83xx_get_mbx_data(struct qlcnic_adapter *adapter,
				     struct qlcnic_cmd_args *cmd)
{
	int i;
	for (i = 0; i < cmd->rsp.num; i++)
		cmd->rsp.arg[i] = readl(QLCNIC_MBX_FW(adapter->ahw, i));
}