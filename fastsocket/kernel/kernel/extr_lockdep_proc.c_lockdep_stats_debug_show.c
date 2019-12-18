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
 int /*<<< orphan*/  chain_lookup_hits ; 
 int /*<<< orphan*/  chain_lookup_misses ; 
 unsigned int debug_atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hardirqs_off_events ; 
 int /*<<< orphan*/  hardirqs_on_events ; 
 int /*<<< orphan*/  nr_cyclic_checks ; 
 int /*<<< orphan*/  nr_find_usage_backwards_checks ; 
 int /*<<< orphan*/  nr_find_usage_forwards_checks ; 
 int /*<<< orphan*/  redundant_hardirqs_off ; 
 int /*<<< orphan*/  redundant_hardirqs_on ; 
 int /*<<< orphan*/  redundant_softirqs_off ; 
 int /*<<< orphan*/  redundant_softirqs_on ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int) ; 
 int /*<<< orphan*/  softirqs_off_events ; 
 int /*<<< orphan*/  softirqs_on_events ; 

__attribute__((used)) static void lockdep_stats_debug_show(struct seq_file *m)
{
#ifdef CONFIG_DEBUG_LOCKDEP
	unsigned int hi1 = debug_atomic_read(&hardirqs_on_events),
		     hi2 = debug_atomic_read(&hardirqs_off_events),
		     hr1 = debug_atomic_read(&redundant_hardirqs_on),
		     hr2 = debug_atomic_read(&redundant_hardirqs_off),
		     si1 = debug_atomic_read(&softirqs_on_events),
		     si2 = debug_atomic_read(&softirqs_off_events),
		     sr1 = debug_atomic_read(&redundant_softirqs_on),
		     sr2 = debug_atomic_read(&redundant_softirqs_off);

	seq_printf(m, " chain lookup misses:           %11u\n",
		debug_atomic_read(&chain_lookup_misses));
	seq_printf(m, " chain lookup hits:             %11u\n",
		debug_atomic_read(&chain_lookup_hits));
	seq_printf(m, " cyclic checks:                 %11u\n",
		debug_atomic_read(&nr_cyclic_checks));
	seq_printf(m, " find-mask forwards checks:     %11u\n",
		debug_atomic_read(&nr_find_usage_forwards_checks));
	seq_printf(m, " find-mask backwards checks:    %11u\n",
		debug_atomic_read(&nr_find_usage_backwards_checks));

	seq_printf(m, " hardirq on events:             %11u\n", hi1);
	seq_printf(m, " hardirq off events:            %11u\n", hi2);
	seq_printf(m, " redundant hardirq ons:         %11u\n", hr1);
	seq_printf(m, " redundant hardirq offs:        %11u\n", hr2);
	seq_printf(m, " softirq on events:             %11u\n", si1);
	seq_printf(m, " softirq off events:            %11u\n", si2);
	seq_printf(m, " redundant softirq ons:         %11u\n", sr1);
	seq_printf(m, " redundant softirq offs:        %11u\n", sr2);
#endif
}