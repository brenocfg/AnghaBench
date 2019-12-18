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
typedef  int /*<<< orphan*/  u32 ;
struct cluster {int highest_slave; struct _zone* owner; struct cluster* nodes; scalar_t__ highest_node; int /*<<< orphan*/  addr; } ;
struct _zone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LOWEST_SLAVE ; 
 scalar_t__ in_own_cluster (int /*<<< orphan*/ ) ; 
 struct cluster* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cluster*) ; 
 struct cluster* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cluster (int /*<<< orphan*/ ) ; 
 struct cluster* tipc_local_nodes ; 
 int tipc_max_nodes ; 
 int tipc_max_slaves ; 
 int /*<<< orphan*/  tipc_zone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_zone_attach_cluster (struct _zone*,struct cluster*) ; 
 struct _zone* tipc_zone_create (int /*<<< orphan*/ ) ; 
 struct _zone* tipc_zone_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

struct cluster *tipc_cltr_create(u32 addr)
{
	struct _zone *z_ptr;
	struct cluster *c_ptr;
	int max_nodes;

	c_ptr = kzalloc(sizeof(*c_ptr), GFP_ATOMIC);
	if (c_ptr == NULL) {
		warn("Cluster creation failure, no memory\n");
		return NULL;
	}

	c_ptr->addr = tipc_addr(tipc_zone(addr), tipc_cluster(addr), 0);
	if (in_own_cluster(addr))
		max_nodes = LOWEST_SLAVE + tipc_max_slaves;
	else
		max_nodes = tipc_max_nodes + 1;

	c_ptr->nodes = kcalloc(max_nodes + 1, sizeof(void*), GFP_ATOMIC);
	if (c_ptr->nodes == NULL) {
		warn("Cluster creation failure, no memory for node area\n");
		kfree(c_ptr);
		return NULL;
	}

	if (in_own_cluster(addr))
		tipc_local_nodes = c_ptr->nodes;
	c_ptr->highest_slave = LOWEST_SLAVE - 1;
	c_ptr->highest_node = 0;

	z_ptr = tipc_zone_find(tipc_zone(addr));
	if (!z_ptr) {
		z_ptr = tipc_zone_create(addr);
	}
	if (!z_ptr) {
		kfree(c_ptr->nodes);
		kfree(c_ptr);
		return NULL;
	}

	tipc_zone_attach_cluster(z_ptr, c_ptr);
	c_ptr->owner = z_ptr;
	return c_ptr;
}