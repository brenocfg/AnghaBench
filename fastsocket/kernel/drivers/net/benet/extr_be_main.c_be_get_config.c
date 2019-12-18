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
typedef  int /*<<< orphan*/  u32 ;
struct be_adapter {int /*<<< orphan*/  cfg_num_qs; int /*<<< orphan*/  pmac_id; int /*<<< orphan*/  asic_rev; int /*<<< orphan*/  function_caps; int /*<<< orphan*/  function_mode; int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int be_cmd_query_fw_cfg (struct be_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int be_get_resources (struct be_adapter*) ; 
 int /*<<< orphan*/  be_max_qs (struct be_adapter*) ; 
 scalar_t__ be_max_uc (struct be_adapter*) ; 
 int /*<<< orphan*/  kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int be_get_config(struct be_adapter *adapter)
{
	int status;

	status = be_cmd_query_fw_cfg(adapter, &adapter->port_num,
				     &adapter->function_mode,
				     &adapter->function_caps,
				     &adapter->asic_rev);
	if (status)
		return status;

	status = be_get_resources(adapter);
	if (status)
		return status;

	/* primary mac needs 1 pmac entry */
	adapter->pmac_id = kcalloc(be_max_uc(adapter) + 1, sizeof(u32),
				   GFP_KERNEL);
	if (!adapter->pmac_id)
		return -ENOMEM;

	/* Sanitize cfg_num_qs based on HW and platform limits */
	adapter->cfg_num_qs = min(adapter->cfg_num_qs, be_max_qs(adapter));

	return 0;
}