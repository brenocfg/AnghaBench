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
struct seq_file {int dummy; } ;
struct TYPE_6__ {TYPE_2__* nsproxy; } ;
struct TYPE_5__ {TYPE_1__* pid_ns; } ;
struct TYPE_4__ {int /*<<< orphan*/  last_pid; } ;

/* Variables and functions */
 int FIXED_1 ; 
 int /*<<< orphan*/  LOAD_FRAC (int) ; 
 int /*<<< orphan*/  LOAD_INT (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  count_active_contexts () ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  nr_spu_contexts ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* spu_avenrun ; 

__attribute__((used)) static int show_spu_loadavg(struct seq_file *s, void *private)
{
	int a, b, c;

	a = spu_avenrun[0] + (FIXED_1/200);
	b = spu_avenrun[1] + (FIXED_1/200);
	c = spu_avenrun[2] + (FIXED_1/200);

	/*
	 * Note that last_pid doesn't really make much sense for the
	 * SPU loadavg (it even seems very odd on the CPU side...),
	 * but we include it here to have a 100% compatible interface.
	 */
	seq_printf(s, "%d.%02d %d.%02d %d.%02d %ld/%d %d\n",
		LOAD_INT(a), LOAD_FRAC(a),
		LOAD_INT(b), LOAD_FRAC(b),
		LOAD_INT(c), LOAD_FRAC(c),
		count_active_contexts(),
		atomic_read(&nr_spu_contexts),
		current->nsproxy->pid_ns->last_pid);
	return 0;
}