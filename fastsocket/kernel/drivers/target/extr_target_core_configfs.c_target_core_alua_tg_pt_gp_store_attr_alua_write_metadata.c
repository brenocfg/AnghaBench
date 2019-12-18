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
struct t10_alua_tg_pt_gp {int tg_pt_gp_write_metadata; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int strict_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t target_core_alua_tg_pt_gp_store_attr_alua_write_metadata(
	struct t10_alua_tg_pt_gp *tg_pt_gp,
	const char *page,
	size_t count)
{
	unsigned long tmp;
	int ret;

	ret = strict_strtoul(page, 0, &tmp);
	if (ret < 0) {
		pr_err("Unable to extract alua_write_metadata\n");
		return -EINVAL;
	}

	if ((tmp != 0) && (tmp != 1)) {
		pr_err("Illegal value for alua_write_metadata:"
			" %lu\n", tmp);
		return -EINVAL;
	}
	tg_pt_gp->tg_pt_gp_write_metadata = (int)tmp;

	return count;
}