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
struct recent_table {int /*<<< orphan*/  lru_list; } ;
struct recent_entry {int /*<<< orphan*/  lru_list; int /*<<< orphan*/  index; int /*<<< orphan*/  nstamps; int /*<<< orphan*/ * stamps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_pkt_list_tot ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recent_entry_update(struct recent_table *t, struct recent_entry *e)
{
	e->index %= ip_pkt_list_tot;
	e->stamps[e->index++] = jiffies;
	if (e->index > e->nstamps)
		e->nstamps = e->index;
	list_move_tail(&e->lru_list, &t->lru_list);
}