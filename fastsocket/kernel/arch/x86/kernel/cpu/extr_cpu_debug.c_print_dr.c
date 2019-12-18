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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_debugreg (unsigned long,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void print_dr(void *arg)
{
	struct seq_file *seq = arg;
	unsigned long dr;
	int i;

	for (i = 0; i < 8; i++) {
		/* Ignore db4, db5 */
		if ((i == 4) || (i == 5))
			continue;
		get_debugreg(dr, i);
		seq_printf(seq, " dr%d\t: %016lx\n", i, dr);
	}

	seq_printf(seq, "\n MSR\t:\n");
}