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
typedef  int u32 ;
struct cluster {int dummy; } ;
struct _zone {struct cluster** clusters; } ;

/* Variables and functions */
 int tipc_cltr_select_router (struct cluster*,int) ; 
 size_t tipc_cluster (int) ; 
 int tipc_max_clusters ; 

u32 tipc_zone_select_router(struct _zone *z_ptr, u32 addr, u32 ref)
{
	struct cluster *c_ptr;
	u32 c_num;
	u32 router;

	if (!z_ptr)
		return 0;
	c_ptr = z_ptr->clusters[tipc_cluster(addr)];
	router = c_ptr ? tipc_cltr_select_router(c_ptr, ref) : 0;
	if (router)
		return router;

	/* Links to any other clusters within the zone? */
	for (c_num = 1; c_num <= tipc_max_clusters; c_num++) {
		c_ptr = z_ptr->clusters[c_num];
		router = c_ptr ? tipc_cltr_select_router(c_ptr, ref) : 0;
		if (router)
			return router;
	}
	return 0;
}