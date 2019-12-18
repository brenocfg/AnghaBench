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
struct kmem_cache_order_objects {int member_0; } ;

/* Variables and functions */
 int OO_SHIFT ; 
 int PAGE_SIZE ; 

__attribute__((used)) static inline struct kmem_cache_order_objects oo_make(int order,
						unsigned long size)
{
	struct kmem_cache_order_objects x = {
		(order << OO_SHIFT) + (PAGE_SIZE << order) / size
	};

	return x;
}