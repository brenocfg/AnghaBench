#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int entry_mask; int entry_shift; int sets; unsigned long long way_size; unsigned long long ways; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ dcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  SH_CACHE_MODE_WT ; 
 int /*<<< orphan*/  __raw_readb (unsigned long) ; 
 TYPE_2__* cpu_data ; 
 scalar_t__ dummy_alloco_area ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inline sh64_dcache_purge_sets(int sets_to_purge_base, int n_sets)
{
	/* Purge all ways in a particular block of sets, specified by the base
	   set number and number of sets.  Can handle wrap-around, if that's
	   needed.  */

	int dummy_buffer_base_set;
	unsigned long long eaddr, eaddr0, eaddr1;
	int j;
	int set_offset;

	dummy_buffer_base_set = ((int)&dummy_alloco_area &
				 cpu_data->dcache.entry_mask) >>
				 cpu_data->dcache.entry_shift;
	set_offset = sets_to_purge_base - dummy_buffer_base_set;

	for (j = 0; j < n_sets; j++, set_offset++) {
		set_offset &= (cpu_data->dcache.sets - 1);
		eaddr0 = (unsigned long long)dummy_alloco_area +
			(set_offset << cpu_data->dcache.entry_shift);

		/*
		 * Do one alloco which hits the required set per cache
		 * way.  For write-back mode, this will purge the #ways
		 * resident lines.  There's little point unrolling this
		 * loop because the allocos stall more if they're too
		 * close together.
		 */
		eaddr1 = eaddr0 + cpu_data->dcache.way_size *
				  cpu_data->dcache.ways;

		for (eaddr = eaddr0; eaddr < eaddr1;
		     eaddr += cpu_data->dcache.way_size) {
			__asm__ __volatile__ ("alloco %0, 0" : : "r" (eaddr));
			__asm__ __volatile__ ("synco"); /* TAKum03020 */
		}

		eaddr1 = eaddr0 + cpu_data->dcache.way_size *
				  cpu_data->dcache.ways;

		for (eaddr = eaddr0; eaddr < eaddr1;
		     eaddr += cpu_data->dcache.way_size) {
			/*
			 * Load from each address.  Required because
			 * alloco is a NOP if the cache is write-through.
			 */
			if (test_bit(SH_CACHE_MODE_WT, &(cpu_data->dcache.flags)))
				__raw_readb((unsigned long)eaddr);
		}
	}

	/*
	 * Don't use OCBI to invalidate the lines.  That costs cycles
	 * directly.  If the dummy block is just left resident, it will
	 * naturally get evicted as required.
	 */
}