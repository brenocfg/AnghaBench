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

/* Variables and functions */
 int NBR_OF_CLIENTS ; 
 scalar_t__ NBR_OF_SLOTS ; 
 scalar_t__** active_clients ; 
 int /*<<< orphan*/  crisv32_arbiter_config (int,scalar_t__) ; 
 scalar_t__** requested_slots ; 

void crisv32_arbiter_deallocate_bandwidth(int client, int region)
{
	int i;
	int total_assigned = 0;

	requested_slots[region][client] = 0;
	active_clients[region][client] = 0;

	for (i = 0; i < NBR_OF_CLIENTS; i++)
		total_assigned += requested_slots[region][i];

	crisv32_arbiter_config(region, NBR_OF_SLOTS - total_assigned);
}