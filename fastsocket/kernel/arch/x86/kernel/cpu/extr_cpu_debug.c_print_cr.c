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
 int /*<<< orphan*/  read_cr0 () ; 
 int /*<<< orphan*/  read_cr2 () ; 
 int /*<<< orphan*/  read_cr3 () ; 
 int /*<<< orphan*/  read_cr4_safe () ; 
 int /*<<< orphan*/  read_cr8 () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_cr(void *arg)
{
	struct seq_file *seq = arg;

	seq_printf(seq, " cr0\t: %016lx\n", read_cr0());
	seq_printf(seq, " cr2\t: %016lx\n", read_cr2());
	seq_printf(seq, " cr3\t: %016lx\n", read_cr3());
	seq_printf(seq, " cr4\t: %016lx\n", read_cr4_safe());
#ifdef CONFIG_X86_64
	seq_printf(seq, " cr8\t: %016lx\n", read_cr8());
#endif
}