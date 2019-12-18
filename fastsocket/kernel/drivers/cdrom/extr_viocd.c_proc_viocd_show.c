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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  model; int /*<<< orphan*/  type; int /*<<< orphan*/  rsrcname; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* viocd_diskinfo ; 
 int viocd_numdev ; 

__attribute__((used)) static int proc_viocd_show(struct seq_file *m, void *v)
{
	int i;

	for (i = 0; i < viocd_numdev; i++) {
		seq_printf(m, "viocd device %d is iSeries resource %10.10s"
				"type %4.4s, model %3.3s\n",
				i, viocd_diskinfo[i].rsrcname,
				viocd_diskinfo[i].type,
				viocd_diskinfo[i].model);
	}
	return 0;
}