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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  filter_flags; } ;
struct il_priv {int /*<<< orphan*/  mutex; TYPE_1__ staging; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*,scalar_t__) ; 
 int /*<<< orphan*/  IL_WARN (char*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 struct il_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  il3945_commit_rxon (struct il_priv*) ; 
 scalar_t__ il_scan_cancel_timeout (struct il_priv*,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
il3945_store_filter_flags(struct device *d, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct il_priv *il = dev_get_drvdata(d);
	u32 filter_flags = simple_strtoul(buf, NULL, 0);

	mutex_lock(&il->mutex);
	if (le32_to_cpu(il->staging.filter_flags) != filter_flags) {
		/* Cancel any currently running scans... */
		if (il_scan_cancel_timeout(il, 100))
			IL_WARN("Could not cancel scan.\n");
		else {
			D_INFO("Committing rxon.filter_flags = " "0x%04X\n",
			       filter_flags);
			il->staging.filter_flags = cpu_to_le32(filter_flags);
			il3945_commit_rxon(il);
		}
	}
	mutex_unlock(&il->mutex);

	return count;
}