#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int s8 ;
struct TYPE_2__ {int nbr_clients; int** requested_slots; int /*<<< orphan*/ ** active_clients; } ;

/* Variables and functions */
 int EXT_REGION ; 
 int INT_REGION ; 
 int NBR_OF_SLOTS ; 
 int /*<<< orphan*/  REG_WR_INT_VECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* arbiters ; 
 int /*<<< orphan*/  marb_bar ; 
 int /*<<< orphan*/  marb_foo ; 
 int /*<<< orphan*/  regi_marb_bar ; 
 int /*<<< orphan*/  regi_marb_foo ; 
 int /*<<< orphan*/  rw_ddr2_slots ; 
 int /*<<< orphan*/  rw_intm_slots ; 
 int /*<<< orphan*/  rw_l2_slots ; 

__attribute__((used)) static void crisv32_arbiter_config(int arbiter, int region, int unused_slots)
{
	int slot;
	int client;
	int interval = 0;

	/*
	 * This vector corresponds to the hardware arbiter slots (see
	 * the hardware documentation for semantics). We initialize
	 * each slot with a suitable sentinel value outside the valid
	 * range {0 .. NBR_OF_CLIENTS - 1} and replace them with
	 * client indexes. Then it's fed to the hardware.
	 */
	s8 val[NBR_OF_SLOTS];

	for (slot = 0; slot < NBR_OF_SLOTS; slot++)
	    val[slot] = -1;

	for (client = 0; client < arbiters[arbiter].nbr_clients; client++) {
	    int pos;
	    /* Allocate the requested non-zero number of slots, but
	     * also give clients with zero-requests one slot each
	     * while stocks last. We do the latter here, in client
	     * order. This makes sure zero-request clients are the
	     * first to get to any spare slots, else those slots
	     * could, when bandwidth is allocated close to the limit,
	     * all be allocated to low-index non-zero-request clients
	     * in the default-fill loop below. Another positive but
	     * secondary effect is a somewhat better spread of the
	     * zero-bandwidth clients in the vector, avoiding some of
	     * the latency that could otherwise be caused by the
	     * partitioning of non-zero-bandwidth clients at low
	     * indexes and zero-bandwidth clients at high
	     * indexes. (Note that this spreading can only affect the
	     * unallocated bandwidth.)  All the above only matters for
	     * memory-intensive situations, of course.
	     */
	    if (!arbiters[arbiter].requested_slots[region][client]) {
		/*
		 * Skip inactive clients. Also skip zero-slot
		 * allocations in this pass when there are no known
		 * free slots.
		 */
		if (!arbiters[arbiter].active_clients[region][client] ||
				unused_slots <= 0)
			continue;

		unused_slots--;

		/* Only allocate one slot for this client. */
		interval = NBR_OF_SLOTS;
	    } else
		interval = NBR_OF_SLOTS /
			arbiters[arbiter].requested_slots[region][client];

	    pos = 0;
	    while (pos < NBR_OF_SLOTS) {
		if (val[pos] >= 0)
		   pos++;
		else {
			val[pos] = client;
			pos += interval;
		}
	    }
	}

	client = 0;
	for (slot = 0; slot < NBR_OF_SLOTS; slot++) {
		/*
		 * Allocate remaining slots in round-robin
		 * client-number order for active clients. For this
		 * pass, we ignore requested bandwidth and previous
		 * allocations.
		 */
		if (val[slot] < 0) {
			int first = client;
			while (!arbiters[arbiter].active_clients[region][client]) {
				client = (client + 1) %
					arbiters[arbiter].nbr_clients;
				if (client == first)
				   break;
			}
			val[slot] = client;
			client = (client + 1) % arbiters[arbiter].nbr_clients;
		}
		if (arbiter == 0) {
			if (region == EXT_REGION)
				REG_WR_INT_VECT(marb_foo, regi_marb_foo,
					rw_l2_slots, slot, val[slot]);
			else if (region == INT_REGION)
				REG_WR_INT_VECT(marb_foo, regi_marb_foo,
					rw_intm_slots, slot, val[slot]);
		} else {
			REG_WR_INT_VECT(marb_bar, regi_marb_bar,
				rw_ddr2_slots, slot, val[slot]);
		}
	}
}