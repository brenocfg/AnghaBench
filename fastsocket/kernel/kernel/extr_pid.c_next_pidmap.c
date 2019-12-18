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
struct pidmap {int /*<<< orphan*/  page; } ;
struct pid_namespace {struct pidmap* pidmap; } ;

/* Variables and functions */
 unsigned int BITS_PER_PAGE ; 
 unsigned int BITS_PER_PAGE_MASK ; 
 size_t PIDMAP_ENTRIES ; 
 unsigned int PID_MAX_LIMIT ; 
 int find_next_bit (int /*<<< orphan*/ ,unsigned int,int) ; 
 int mk_pid (struct pid_namespace*,struct pidmap*,int) ; 
 scalar_t__ unlikely (int) ; 

int next_pidmap(struct pid_namespace *pid_ns, unsigned int last)
{
	int offset;
	struct pidmap *map, *end;

	if (last >= PID_MAX_LIMIT)
		return -1;

	offset = (last + 1) & BITS_PER_PAGE_MASK;
	map = &pid_ns->pidmap[(last + 1)/BITS_PER_PAGE];
	end = &pid_ns->pidmap[PIDMAP_ENTRIES];
	for (; map < end; map++, offset = 0) {
		if (unlikely(!map->page))
			continue;
		offset = find_next_bit((map)->page, BITS_PER_PAGE, offset);
		if (offset < BITS_PER_PAGE)
			return mk_pid(pid_ns, map, offset);
	}
	return -1;
}