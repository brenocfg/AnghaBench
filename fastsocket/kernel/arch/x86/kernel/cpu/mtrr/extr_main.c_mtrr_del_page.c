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
typedef  int /*<<< orphan*/  mtrr_type ;
struct TYPE_2__ {int /*<<< orphan*/  (* get ) (int,unsigned long*,unsigned long*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  get_online_cpus () ; 
 TYPE_1__* mtrr_if ; 
 int /*<<< orphan*/  mtrr_mutex ; 
 int* mtrr_usage_table ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int num_var_ranges ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  set_mtrr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int,unsigned long*,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,unsigned long*,unsigned long*,int /*<<< orphan*/ *) ; 

int mtrr_del_page(int reg, unsigned long base, unsigned long size)
{
	int i, max;
	mtrr_type ltype;
	unsigned long lbase, lsize;
	int error = -EINVAL;

	if (!mtrr_if)
		return -ENXIO;

	max = num_var_ranges;
	/* No CPU hotplug when we change MTRR entries */
	get_online_cpus();
	mutex_lock(&mtrr_mutex);
	if (reg < 0) {
		/*  Search for existing MTRR  */
		for (i = 0; i < max; ++i) {
			mtrr_if->get(i, &lbase, &lsize, &ltype);
			if (lbase == base && lsize == size) {
				reg = i;
				break;
			}
		}
		if (reg < 0) {
			pr_debug("mtrr: no MTRR for %lx000,%lx000 found\n",
				 base, size);
			goto out;
		}
	}
	if (reg >= max) {
		pr_warning("mtrr: register: %d too big\n", reg);
		goto out;
	}
	mtrr_if->get(reg, &lbase, &lsize, &ltype);
	if (lsize < 1) {
		pr_warning("mtrr: MTRR %d not used\n", reg);
		goto out;
	}
	if (mtrr_usage_table[reg] < 1) {
		pr_warning("mtrr: reg: %d has count=0\n", reg);
		goto out;
	}
	if (--mtrr_usage_table[reg] < 1)
		set_mtrr(reg, 0, 0, 0, false);
	error = reg;
 out:
	mutex_unlock(&mtrr_mutex);
	put_online_cpus();
	return error;
}