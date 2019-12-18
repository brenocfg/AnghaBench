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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  symbol_filter_t ;
struct thread {int dummy; } ;
struct machine {int dummy; } ;
struct addr_location {int /*<<< orphan*/ * sym; int /*<<< orphan*/  addr; int /*<<< orphan*/ * map; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 int /*<<< orphan*/ * map__find_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__find_addr_map (struct thread*,struct machine*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct addr_location*) ; 

void thread__find_addr_location(struct thread *thread, struct machine *machine,
				u8 cpumode, enum map_type type, u64 addr,
				struct addr_location *al,
				symbol_filter_t filter)
{
	thread__find_addr_map(thread, machine, cpumode, type, addr, al);
	if (al->map != NULL)
		al->sym = map__find_symbol(al->map, al->addr, filter);
	else
		al->sym = NULL;
}