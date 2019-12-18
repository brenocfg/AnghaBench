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
struct raid6_calls {scalar_t__ prefer; int /*<<< orphan*/  name; int /*<<< orphan*/  (* gen_syndrome ) (int const,int /*<<< orphan*/ ,void**) ;int /*<<< orphan*/  (* valid ) () ;} ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int RAID6_TIME_JIFFIES_LG2 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 struct raid6_calls** raid6_algos ; 
 struct raid6_calls raid6_call ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (int const,int /*<<< orphan*/ ,void**) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static inline const struct raid6_calls *raid6_choose_gen(
	void *(*const dptrs)[(65536/PAGE_SIZE)+2], const int disks)
{
	unsigned long perf, bestperf, j0, j1;
	const struct raid6_calls *const *algo;
	const struct raid6_calls *best;

	for (bestperf = 0, best = NULL, algo = raid6_algos; *algo; algo++) {
		if (!best || (*algo)->prefer >= best->prefer) {
			if ((*algo)->valid && !(*algo)->valid())
				continue;

			perf = 0;

			preempt_disable();
			j0 = jiffies;
			while ((j1 = jiffies) == j0)
				cpu_relax();
			while (time_before(jiffies,
					    j1 + (1<<RAID6_TIME_JIFFIES_LG2))) {
				(*algo)->gen_syndrome(disks, PAGE_SIZE, *dptrs);
				perf++;
			}
			preempt_enable();

			if (perf > bestperf) {
				bestperf = perf;
				best = *algo;
			}
			printk("raid6: %-8s %5ld MB/s\n", (*algo)->name,
			       (perf*HZ) >> (20-16+RAID6_TIME_JIFFIES_LG2));
		}
	}

	if (best) {
		printk("raid6: using algorithm %s (%ld MB/s)\n",
		       best->name,
		       (bestperf*HZ) >> (20-16+RAID6_TIME_JIFFIES_LG2));
		raid6_call = *best;
	} else
		printk("raid6: Yikes!  No algorithm found!\n");

	return best;
}