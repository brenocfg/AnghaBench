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
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ cheetah ; 
 scalar_t__ cheetah_plus ; 
 int /*<<< orphan*/  dcpage_flushes ; 
 int /*<<< orphan*/  dcpage_flushes_xcall ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 scalar_t__ spitfire ; 
 scalar_t__ tlb_type ; 

void mmu_info(struct seq_file *m)
{
	if (tlb_type == cheetah)
		seq_printf(m, "MMU Type\t: Cheetah\n");
	else if (tlb_type == cheetah_plus)
		seq_printf(m, "MMU Type\t: Cheetah+\n");
	else if (tlb_type == spitfire)
		seq_printf(m, "MMU Type\t: Spitfire\n");
	else if (tlb_type == hypervisor)
		seq_printf(m, "MMU Type\t: Hypervisor (sun4v)\n");
	else
		seq_printf(m, "MMU Type\t: ???\n");

#ifdef CONFIG_DEBUG_DCFLUSH
	seq_printf(m, "DCPageFlushes\t: %d\n",
		   atomic_read(&dcpage_flushes));
#ifdef CONFIG_SMP
	seq_printf(m, "DCPageFlushesXC\t: %d\n",
		   atomic_read(&dcpage_flushes_xcall));
#endif /* CONFIG_SMP */
#endif /* CONFIG_DEBUG_DCFLUSH */
}