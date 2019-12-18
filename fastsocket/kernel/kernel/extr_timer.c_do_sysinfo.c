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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct sysinfo {unsigned long totalram; unsigned long totalswap; unsigned int mem_unit; unsigned int freeram; unsigned int sharedram; unsigned int bufferram; unsigned int freeswap; unsigned int totalhigh; unsigned int freehigh; int /*<<< orphan*/  procs; int /*<<< orphan*/  loads; scalar_t__ uptime; } ;

/* Variables and functions */
 scalar_t__ FSHIFT ; 
 scalar_t__ SI_LOAD_SHIFT ; 
 int /*<<< orphan*/  get_avenrun (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ktime_get_ts (struct timespec*) ; 
 int /*<<< orphan*/  memset (struct sysinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  monotonic_to_bootbased (struct timespec*) ; 
 int /*<<< orphan*/  nr_threads ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 
 int /*<<< orphan*/  si_swapinfo (struct sysinfo*) ; 

int do_sysinfo(struct sysinfo *info)
{
	unsigned long mem_total, sav_total;
	unsigned int mem_unit, bitcount;
	struct timespec tp;

	memset(info, 0, sizeof(struct sysinfo));

	ktime_get_ts(&tp);
	monotonic_to_bootbased(&tp);
	info->uptime = tp.tv_sec + (tp.tv_nsec ? 1 : 0);

	get_avenrun(info->loads, 0, SI_LOAD_SHIFT - FSHIFT);

	info->procs = nr_threads;

	si_meminfo(info);
	si_swapinfo(info);

	/*
	 * If the sum of all the available memory (i.e. ram + swap)
	 * is less than can be stored in a 32 bit unsigned long then
	 * we can be binary compatible with 2.2.x kernels.  If not,
	 * well, in that case 2.2.x was broken anyways...
	 *
	 *  -Erik Andersen <andersee@debian.org>
	 */

	mem_total = info->totalram + info->totalswap;
	if (mem_total < info->totalram || mem_total < info->totalswap)
		goto out;
	bitcount = 0;
	mem_unit = info->mem_unit;
	while (mem_unit > 1) {
		bitcount++;
		mem_unit >>= 1;
		sav_total = mem_total;
		mem_total <<= 1;
		if (mem_total < sav_total)
			goto out;
	}

	/*
	 * If mem_total did not overflow, multiply all memory values by
	 * info->mem_unit and set it to 1.  This leaves things compatible
	 * with 2.2.x, and also retains compatibility with earlier 2.4.x
	 * kernels...
	 */

	info->mem_unit = 1;
	info->totalram <<= bitcount;
	info->freeram <<= bitcount;
	info->sharedram <<= bitcount;
	info->bufferram <<= bitcount;
	info->totalswap <<= bitcount;
	info->freeswap <<= bitcount;
	info->totalhigh <<= bitcount;
	info->freehigh <<= bitcount;

out:
	return 0;
}