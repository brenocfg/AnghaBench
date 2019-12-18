#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
struct map_groups {int dummy; } ;
struct thread {struct map_groups mg; } ;
struct machine {struct map_groups kmaps; } ;
struct addr_location {int filtered; char level; scalar_t__ addr; TYPE_1__* map; scalar_t__ cpumode; struct thread* thread; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;
struct TYPE_3__ {scalar_t__ (* map_ip ) (TYPE_1__*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ PERF_RECORD_MISC_GUEST_KERNEL ; 
 scalar_t__ PERF_RECORD_MISC_GUEST_USER ; 
 scalar_t__ PERF_RECORD_MISC_KERNEL ; 
 scalar_t__ PERF_RECORD_MISC_USER ; 
 TYPE_1__* map_groups__find (struct map_groups*,int,scalar_t__) ; 
 scalar_t__ perf_guest ; 
 scalar_t__ perf_host ; 
 scalar_t__ stub1 (TYPE_1__*,scalar_t__) ; 

void thread__find_addr_map(struct thread *self,
			   struct machine *machine, u8 cpumode,
			   enum map_type type, u64 addr,
			   struct addr_location *al)
{
	struct map_groups *mg = &self->mg;

	al->thread = self;
	al->addr = addr;
	al->cpumode = cpumode;
	al->filtered = false;

	if (machine == NULL) {
		al->map = NULL;
		return;
	}

	if (cpumode == PERF_RECORD_MISC_KERNEL && perf_host) {
		al->level = 'k';
		mg = &machine->kmaps;
	} else if (cpumode == PERF_RECORD_MISC_USER && perf_host) {
		al->level = '.';
	} else if (cpumode == PERF_RECORD_MISC_GUEST_KERNEL && perf_guest) {
		al->level = 'g';
		mg = &machine->kmaps;
	} else {
		/*
		 * 'u' means guest os user space.
		 * TODO: We don't support guest user space. Might support late.
		 */
		if (cpumode == PERF_RECORD_MISC_GUEST_USER && perf_guest)
			al->level = 'u';
		else
			al->level = 'H';
		al->map = NULL;

		if ((cpumode == PERF_RECORD_MISC_GUEST_USER ||
			cpumode == PERF_RECORD_MISC_GUEST_KERNEL) &&
			!perf_guest)
			al->filtered = true;
		if ((cpumode == PERF_RECORD_MISC_USER ||
			cpumode == PERF_RECORD_MISC_KERNEL) &&
			!perf_host)
			al->filtered = true;

		return;
	}
try_again:
	al->map = map_groups__find(mg, type, al->addr);
	if (al->map == NULL) {
		/*
		 * If this is outside of all known maps, and is a negative
		 * address, try to look it up in the kernel dso, as it might be
		 * a vsyscall or vdso (which executes in user-mode).
		 *
		 * XXX This is nasty, we should have a symbol list in the
		 * "[vdso]" dso, but for now lets use the old trick of looking
		 * in the whole kernel symbol list.
		 */
		if ((long long)al->addr < 0 &&
		    cpumode == PERF_RECORD_MISC_USER &&
		    machine && mg != &machine->kmaps) {
			mg = &machine->kmaps;
			goto try_again;
		}
	} else
		al->addr = al->map->map_ip(al->map, al->addr);
}