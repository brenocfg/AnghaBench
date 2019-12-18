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
struct super_block {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  filename ;
struct TYPE_2__ {int /*<<< orphan*/  unit_mask; int /*<<< orphan*/  user; int /*<<< orphan*/  kernel; int /*<<< orphan*/  count; int /*<<< orphan*/  event; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 unsigned int NR_counter ; 
 TYPE_1__* counter ; 
 int /*<<< orphan*/  oprofilefs_create_ulong (struct super_block*,struct dentry*,char*,int /*<<< orphan*/ *) ; 
 struct dentry* oprofilefs_mkdir (struct super_block*,struct dentry*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static int avr32_perf_counter_create_files(struct super_block *sb,
		struct dentry *root)
{
	struct dentry *dir;
	unsigned int i;
	char filename[4];

	for (i = 0; i < NR_counter; i++) {
		snprintf(filename, sizeof(filename), "%u", i);
		dir = oprofilefs_mkdir(sb, root, filename);

		oprofilefs_create_ulong(sb, dir, "enabled",
				&counter[i].enabled);
		oprofilefs_create_ulong(sb, dir, "event",
				&counter[i].event);
		oprofilefs_create_ulong(sb, dir, "count",
				&counter[i].count);

		/* Dummy entries */
		oprofilefs_create_ulong(sb, dir, "kernel",
				&counter[i].kernel);
		oprofilefs_create_ulong(sb, dir, "user",
				&counter[i].user);
		oprofilefs_create_ulong(sb, dir, "unit_mask",
				&counter[i].unit_mask);
	}

	return 0;
}