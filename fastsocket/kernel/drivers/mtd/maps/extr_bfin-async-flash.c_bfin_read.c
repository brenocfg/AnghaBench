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
struct map_info {scalar_t__ virt; scalar_t__ map_priv_1; } ;
struct async_state {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ map_word ;

/* Variables and functions */
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  switch_back (struct async_state*) ; 
 int /*<<< orphan*/  switch_to_flash (struct async_state*) ; 

__attribute__((used)) static map_word bfin_read(struct map_info *map, unsigned long ofs)
{
	struct async_state *state = (struct async_state *)map->map_priv_1;
	uint16_t word;
	map_word test;

	switch_to_flash(state);

	word = readw(map->virt + ofs);

	switch_back(state);

	test.x[0] = word;
	return test;
}