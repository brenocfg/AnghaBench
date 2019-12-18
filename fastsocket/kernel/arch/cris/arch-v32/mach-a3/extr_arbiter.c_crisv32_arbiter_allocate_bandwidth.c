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
struct TYPE_2__ {int nbr_clients; int** requested_slots; int** active_clients; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EXT_REGION ; 
 unsigned long NBR_OF_SLOTS ; 
 TYPE_1__* arbiters ; 
 int /*<<< orphan*/  crisv32_arbiter_config (int,int,unsigned long) ; 
 int /*<<< orphan*/  crisv32_arbiter_init () ; 
 unsigned long* max_bandwidth ; 

int crisv32_arbiter_allocate_bandwidth(int client, int region,
				      unsigned long bandwidth)
{
	int i;
	int total_assigned = 0;
	int total_clients = 0;
	int req;
	int arbiter = 0;

	crisv32_arbiter_init();

	if (client & 0xffff0000) {
		arbiter = 1;
		client >>= 16;
	}

	for (i = 0; i < arbiters[arbiter].nbr_clients; i++) {
		total_assigned += arbiters[arbiter].requested_slots[region][i];
		total_clients += arbiters[arbiter].active_clients[region][i];
	}

	/* Avoid division by 0 for 0-bandwidth requests. */
	req = bandwidth == 0
		? 0 : NBR_OF_SLOTS / (max_bandwidth[region] / bandwidth);

	/*
	 * We make sure that there are enough slots only for non-zero
	 * requests. Requesting 0 bandwidth *may* allocate slots,
	 * though if all bandwidth is allocated, such a client won't
	 * get any and will have to rely on getting memory access
	 * according to the fixed scheme that's the default when one
	 * of the slot-allocated clients doesn't claim their slot.
	 */
	if (total_assigned + req > NBR_OF_SLOTS)
	   return -ENOMEM;

	arbiters[arbiter].active_clients[region][client] = 1;
	arbiters[arbiter].requested_slots[region][client] = req;
	crisv32_arbiter_config(arbiter, region, NBR_OF_SLOTS - total_assigned);

	/* Propagate allocation from foo to bar */
	if (arbiter == 0)
		crisv32_arbiter_allocate_bandwidth(8 << 16,
			EXT_REGION, bandwidth);
	return 0;
}