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
struct cluster {int dummy; } ;
struct _zone {struct cluster** clusters; } ;

/* Variables and functions */
 struct _zone* tipc_zone_find (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct cluster *tipc_cltr_find(u32 addr)
{
	struct _zone *z_ptr = tipc_zone_find(addr);

	if (z_ptr)
		return z_ptr->clusters[1];
	return NULL;
}