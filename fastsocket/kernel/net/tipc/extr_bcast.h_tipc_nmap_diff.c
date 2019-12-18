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
 int ARRAY_SIZE (int*) ; 
 int WSIZE ; 
 int /*<<< orphan*/  memset (struct tipc_node_map*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void tipc_nmap_diff(struct tipc_node_map *nm_a, struct tipc_node_map *nm_b,
				  struct tipc_node_map *nm_diff)
{
	int stop = ARRAY_SIZE(nm_a->map);
	int w;
	int b;
	u32 map;

	memset(nm_diff, 0, sizeof(*nm_diff));
	for (w = 0; w < stop; w++) {
		map = nm_a->map[w] ^ (nm_a->map[w] & nm_b->map[w]);
		nm_diff->map[w] = map;
		if (map != 0) {
			for (b = 0 ; b < WSIZE; b++) {
				if (map & (1 << b))
					nm_diff->count++;
			}
		}
	}
}