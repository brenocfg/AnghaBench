#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct map_info {scalar_t__ virt; } ;
struct async_state {unsigned long win_size; } ;
struct TYPE_3__ {int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 struct async_state* gf_map_info_to_state (struct map_info*) ; 
 int /*<<< orphan*/  gf_set_gpios (struct async_state*,unsigned long) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 

__attribute__((used)) static map_word gf_read(struct map_info *map, unsigned long ofs)
{
	struct async_state *state = gf_map_info_to_state(map);
	uint16_t word;
	map_word test;

	gf_set_gpios(state, ofs);

	word = readw(map->virt + (ofs % state->win_size));
	test.x[0] = word;
	return test;
}