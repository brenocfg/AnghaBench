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
struct _zone {scalar_t__* clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  tipc_cltr_remove_as_router (scalar_t__,size_t) ; 
 size_t tipc_max_clusters ; 

void tipc_zone_remove_as_router(struct _zone *z_ptr, u32 router)
{
	u32 c_num;

	for (c_num = 1; c_num <= tipc_max_clusters; c_num++) {
		if (z_ptr->clusters[c_num]) {
			tipc_cltr_remove_as_router(z_ptr->clusters[c_num],
						   router);
		}
	}
}