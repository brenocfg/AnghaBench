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
struct thread {int dummy; } ;
struct machine {int dummy; } ;
struct addr_map_symbol {int /*<<< orphan*/  map; scalar_t__ sym; int /*<<< orphan*/  al_addr; int /*<<< orphan*/  addr; } ;
struct addr_location {int /*<<< orphan*/  map; scalar_t__ sym; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  al ;

/* Variables and functions */
 int /*<<< orphan*/  MAP__FUNCTION ; 
 size_t NCPUMODES ; 
 int /*<<< orphan*/ * cpumodes ; 
 int /*<<< orphan*/  memset (struct addr_location*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thread__find_addr_location (struct thread*,struct machine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ip__resolve_ams(struct machine *self, struct thread *thread,
			    struct addr_map_symbol *ams,
			    u64 ip)
{
	struct addr_location al;
	size_t i;
	u8 m;

	memset(&al, 0, sizeof(al));

	for (i = 0; i < NCPUMODES; i++) {
		m = cpumodes[i];
		/*
		 * We cannot use the header.misc hint to determine whether a
		 * branch stack address is user, kernel, guest, hypervisor.
		 * Branches may straddle the kernel/user/hypervisor boundaries.
		 * Thus, we have to try consecutively until we find a match
		 * or else, the symbol is unknown
		 */
		thread__find_addr_location(thread, self, m, MAP__FUNCTION,
				ip, &al, NULL);
		if (al.sym)
			goto found;
	}
found:
	ams->addr = ip;
	ams->al_addr = al.addr;
	ams->sym = al.sym;
	ams->map = al.map;
}