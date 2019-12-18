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
struct map_info {scalar_t__ virt; scalar_t__ map_priv_1; } ;
struct async_state {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SSYNC () ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switch_back (struct async_state*) ; 
 int /*<<< orphan*/  switch_to_flash (struct async_state*) ; 

__attribute__((used)) static void bfin_copy_to(struct map_info *map, unsigned long to, const void *from, ssize_t len)
{
	struct async_state *state = (struct async_state *)map->map_priv_1;

	switch_to_flash(state);

	memcpy(map->virt + to, from, len);
	SSYNC();

	switch_back(state);
}