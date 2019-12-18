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
struct map_info {scalar_t__ virt; } ;
struct async_state {unsigned long win_size; } ;
typedef  unsigned long ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct async_state* gf_map_info_to_state (struct map_info*) ; 
 int /*<<< orphan*/  gf_set_gpios (struct async_state*,unsigned long) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,void const*,unsigned long) ; 

__attribute__((used)) static void gf_copy_to(struct map_info *map, unsigned long to, const void *from, ssize_t len)
{
	struct async_state *state = gf_map_info_to_state(map);

	gf_set_gpios(state, to);

	/* BUG if operation crosses the win_size */
	BUG_ON(!((to + len) % state->win_size <= (to + len)));

	/* operation does not cross the win_size, so one shot it */
	memcpy_toio(map->virt + (to % state->win_size), from, len);
}