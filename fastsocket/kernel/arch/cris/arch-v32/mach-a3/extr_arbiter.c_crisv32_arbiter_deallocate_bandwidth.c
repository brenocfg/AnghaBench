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
struct TYPE_2__ {int nbr_clients; scalar_t__** requested_slots; scalar_t__** active_clients; } ;

/* Variables and functions */
 scalar_t__ NBR_OF_SLOTS ; 
 TYPE_1__* arbiters ; 
 int /*<<< orphan*/  crisv32_arbiter_config (int,int,scalar_t__) ; 

void crisv32_arbiter_deallocate_bandwidth(int client, int region)
{
	int i;
	int total_assigned = 0;
	int arbiter = 0;

	if (client & 0xffff0000)
		arbiter = 1;

	arbiters[arbiter].requested_slots[region][client] = 0;
	arbiters[arbiter].active_clients[region][client] = 0;

	for (i = 0; i < arbiters[arbiter].nbr_clients; i++)
		total_assigned += arbiters[arbiter].requested_slots[region][i];

	crisv32_arbiter_config(arbiter, region, NBR_OF_SLOTS - total_assigned);
}