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
struct thread {int /*<<< orphan*/  mg; } ;
struct map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  map_groups__fixup_overlappings (int /*<<< orphan*/ *,struct map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_groups__insert (int /*<<< orphan*/ *,struct map*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  verbose ; 

void thread__insert_map(struct thread *self, struct map *map)
{
	map_groups__fixup_overlappings(&self->mg, map, verbose, stderr);
	map_groups__insert(&self->mg, map);
}