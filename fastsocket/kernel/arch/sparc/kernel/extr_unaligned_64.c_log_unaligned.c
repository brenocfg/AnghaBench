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
struct pt_regs {scalar_t__ tpc; } ;

/* Variables and functions */
 int HZ ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  printk (char*,scalar_t__,void*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void log_unaligned(struct pt_regs *regs)
{
	static unsigned long count, last_time;

	if (time_after(jiffies, last_time + 5 * HZ))
		count = 0;
	if (count < 5) {
		last_time = jiffies;
		count++;
		printk("Kernel unaligned access at TPC[%lx] %pS\n",
		       regs->tpc, (void *) regs->tpc);
	}
}