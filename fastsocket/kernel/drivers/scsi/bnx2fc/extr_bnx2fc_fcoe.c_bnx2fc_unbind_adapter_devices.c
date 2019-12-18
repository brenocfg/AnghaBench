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
struct bnx2fc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2fc_free_fw_resc (struct bnx2fc_hba*) ; 
 int /*<<< orphan*/  bnx2fc_free_task_ctx (struct bnx2fc_hba*) ; 

__attribute__((used)) static void bnx2fc_unbind_adapter_devices(struct bnx2fc_hba *hba)
{
	bnx2fc_free_fw_resc(hba);
	bnx2fc_free_task_ctx(hba);
}