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
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpu_base ; 
 int cpu_init_regfiles (unsigned int,unsigned int,unsigned int,struct dentry*) ; 
 int /*<<< orphan*/  cpu_reg_range ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  get_cpu_range (unsigned int,unsigned int*,unsigned int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rdmsr_safe_on_cpu (unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static int cpu_init_msr(unsigned cpu, unsigned type, struct dentry *dentry)
{
	struct dentry *cpu_dentry = NULL;
	unsigned reg, reg_min, reg_max;
	int i, err = 0;
	char reg_dir[12];
	u32 low, high;

	for (i = 0; i < ARRAY_SIZE(cpu_reg_range); i++) {
		if (!get_cpu_range(cpu, &reg_min, &reg_max, i,
				   cpu_base[type].flag))
			continue;

		for (reg = reg_min; reg <= reg_max; reg++) {
			if (rdmsr_safe_on_cpu(cpu, reg, &low, &high))
				continue;

			sprintf(reg_dir, "0x%x", reg);
			cpu_dentry = debugfs_create_dir(reg_dir, dentry);
			err = cpu_init_regfiles(cpu, type, reg, cpu_dentry);
			if (err)
				return err;
		}
	}

	return err;
}