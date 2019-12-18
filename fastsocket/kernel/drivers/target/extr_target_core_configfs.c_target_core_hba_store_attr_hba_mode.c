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
struct se_subsystem_api {int (* pmode_enable_hba ) (struct se_hba*,unsigned long) ;} ;
struct se_hba {int /*<<< orphan*/  hba_flags; scalar_t__ dev_count; struct se_subsystem_api* transport; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  HBA_FLAGS_PSCSI_MODE ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int strict_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int stub1 (struct se_hba*,unsigned long) ; 

__attribute__((used)) static ssize_t target_core_hba_store_attr_hba_mode(struct se_hba *hba,
				const char *page, size_t count)
{
	struct se_subsystem_api *transport = hba->transport;
	unsigned long mode_flag;
	int ret;

	if (transport->pmode_enable_hba == NULL)
		return -EINVAL;

	ret = strict_strtoul(page, 0, &mode_flag);
	if (ret < 0) {
		pr_err("Unable to extract hba mode flag: %d\n", ret);
		return -EINVAL;
	}

	if (hba->dev_count) {
		pr_err("Unable to set hba_mode with active devices\n");
		return -EINVAL;
	}

	ret = transport->pmode_enable_hba(hba, mode_flag);
	if (ret < 0)
		return -EINVAL;
	if (ret > 0)
		hba->hba_flags |= HBA_FLAGS_PSCSI_MODE;
	else if (ret == 0)
		hba->hba_flags &= ~HBA_FLAGS_PSCSI_MODE;

	return count;
}