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
typedef  int s8 ;

/* Variables and functions */
 int EXT_REGION ; 
 int INT_REGION ; 
 int NBR_OF_CLIENTS ; 
 int NBR_OF_SLOTS ; 
 int /*<<< orphan*/  REG_WR_INT_VECT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ ** active_clients ; 
 int /*<<< orphan*/  marb ; 
 int /*<<< orphan*/  regi_marb ; 
 int** requested_slots ; 
 int /*<<< orphan*/  rw_ext_slots ; 
 int /*<<< orphan*/  rw_int_slots ; 

__attribute__((used)) static void crisv32_arbiter_config(int region, int unused_slots)
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

	for (client = 0; client < NBR_OF_CLIENTS; client++) {
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
		if (!requested_slots[region][client]) {
			/*
			 * Skip inactive clients. Also skip zero-slot
			 * allocations in this pass when there are no known
			 * free slots.
			 */
			if (!active_clients[region][client]
			    || unused_slots <= 0)
				continue;

			unused_slots--;

			/* Only allocate one slot for this client. */
			interval = NBR_OF_SLOTS;
		} else
			interval =
			    NBR_OF_SLOTS / requested_slots[region][client];

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
			while (!active_clients[region][client]) {
				client = (client + 1) % NBR_OF_CLIENTS;
				if (client == first)
					break;
			}
			val[slot] = client;
			client = (client + 1) % NBR_OF_CLIENTS;
		}
		if (region == EXT_REGION)
			REG_WR_INT_VECT(marb, regi_marb, rw_ext_slots, slot,
					val[slot]);
		else if (region == INT_REGION)
			REG_WR_INT_VECT(marb, regi_marb, rw_int_slots, slot,
					val[slot]);
	}
}