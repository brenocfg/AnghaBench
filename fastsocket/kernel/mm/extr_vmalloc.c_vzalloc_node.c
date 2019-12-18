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
 int GFP_KERNEL ; 
 int __GFP_HIGHMEM ; 
 int __GFP_ZERO ; 
 void* __vmalloc_node_flags (unsigned long,int,int) ; 

void *vzalloc_node(unsigned long size, int node)
{
	return __vmalloc_node_flags(size, node,
			 GFP_KERNEL | __GFP_HIGHMEM | __GFP_ZERO);
}