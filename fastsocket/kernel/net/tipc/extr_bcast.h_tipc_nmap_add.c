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
struct tipc_node_map {int* map; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int WSIZE ; 
 int tipc_node (int) ; 

__attribute__((used)) static inline void tipc_nmap_add(struct tipc_node_map *nm_ptr, u32 node)
{
	int n = tipc_node(node);
	int w = n / WSIZE;
	u32 mask = (1 << (n % WSIZE));

	if ((nm_ptr->map[w] & mask) == 0) {
		nm_ptr->count++;
		nm_ptr->map[w] |= mask;
	}
}