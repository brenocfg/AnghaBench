#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {int enabled; int event; int count; int kernel; int user; int unit_mask; } ;
struct TYPE_5__ {int num_counters; } ;
struct TYPE_4__ {int mmcr0; int mmcr1; int mmcra; int cell_support; int enable_kernel; int enable_user; } ;

/* Variables and functions */
 TYPE_3__* ctr ; 
 TYPE_2__* model ; 
 int /*<<< orphan*/  oprofilefs_create_ulong (struct super_block*,struct dentry*,char*,int*) ; 
 struct dentry* oprofilefs_mkdir (struct super_block*,struct dentry*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 TYPE_1__ sys ; 

__attribute__((used)) static int op_powerpc_create_files(struct super_block *sb, struct dentry *root)
{
	int i;

#ifdef CONFIG_PPC64
	/*
	 * There is one mmcr0, mmcr1 and mmcra for setting the events for
	 * all of the counters.
	 */
	oprofilefs_create_ulong(sb, root, "mmcr0", &sys.mmcr0);
	oprofilefs_create_ulong(sb, root, "mmcr1", &sys.mmcr1);
	oprofilefs_create_ulong(sb, root, "mmcra", &sys.mmcra);
#ifdef CONFIG_OPROFILE_CELL
	/* create a file the user tool can check to see what level of profiling
	 * support exits with this kernel. Initialize bit mask to indicate
	 * what support the kernel has:
	 * bit 0      -  Supports SPU event profiling in addition to PPU
	 *               event and cycles; and SPU cycle profiling
	 * bits 1-31  -  Currently unused.
	 *
	 * If the file does not exist, then the kernel only supports SPU
	 * cycle profiling, PPU event and cycle profiling.
	 */
	oprofilefs_create_ulong(sb, root, "cell_support", &sys.cell_support);
	sys.cell_support = 0x1; /* Note, the user OProfile tool must check
				 * that this bit is set before attempting to
				 * user SPU event profiling.  Older kernels
				 * will not have this file, hence the user
				 * tool is not allowed to do SPU event
				 * profiling on older kernels.  Older kernels
				 * will accept SPU events but collected data
				 * is garbage.
				 */
#endif
#endif

	for (i = 0; i < model->num_counters; ++i) {
		struct dentry *dir;
		char buf[4];

		snprintf(buf, sizeof buf, "%d", i);
		dir = oprofilefs_mkdir(sb, root, buf);

		oprofilefs_create_ulong(sb, dir, "enabled", &ctr[i].enabled);
		oprofilefs_create_ulong(sb, dir, "event", &ctr[i].event);
		oprofilefs_create_ulong(sb, dir, "count", &ctr[i].count);

		/*
		 * Classic PowerPC doesn't support per-counter
		 * control like this, but the options are
		 * expected, so they remain.  For Freescale
		 * Book-E style performance monitors, we do
		 * support them.
		 */
		oprofilefs_create_ulong(sb, dir, "kernel", &ctr[i].kernel);
		oprofilefs_create_ulong(sb, dir, "user", &ctr[i].user);

		oprofilefs_create_ulong(sb, dir, "unit_mask", &ctr[i].unit_mask);
	}

	oprofilefs_create_ulong(sb, root, "enable_kernel", &sys.enable_kernel);
	oprofilefs_create_ulong(sb, root, "enable_user", &sys.enable_user);

	/* Default to tracing both kernel and user */
	sys.enable_kernel = 1;
	sys.enable_user = 1;

	return 0;
}