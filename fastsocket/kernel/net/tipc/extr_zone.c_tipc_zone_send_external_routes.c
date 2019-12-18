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
typedef  size_t u32 ;
struct _zone {scalar_t__* clusters; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ in_own_cluster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cltr_send_ext_routes (scalar_t__,size_t) ; 
 size_t tipc_max_clusters ; 

void tipc_zone_send_external_routes(struct _zone *z_ptr, u32 dest)
{
	u32 c_num;

	for (c_num = 1; c_num <= tipc_max_clusters; c_num++) {
		if (z_ptr->clusters[c_num]) {
			if (in_own_cluster(z_ptr->addr))
				continue;
			tipc_cltr_send_ext_routes(z_ptr->clusters[c_num], dest);
		}
	}
}