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
typedef  void* u64 ;
struct map {int type; int referenced; int erange_warned; int /*<<< orphan*/ * groups; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  unmap_ip; int /*<<< orphan*/  map_ip; struct dso* dso; void* pgoff; void* end; void* start; } ;
struct dso {int dummy; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map__map_ip ; 
 int /*<<< orphan*/  map__unmap_ip ; 

void map__init(struct map *self, enum map_type type,
	       u64 start, u64 end, u64 pgoff, struct dso *dso)
{
	self->type     = type;
	self->start    = start;
	self->end      = end;
	self->pgoff    = pgoff;
	self->dso      = dso;
	self->map_ip   = map__map_ip;
	self->unmap_ip = map__unmap_ip;
	RB_CLEAR_NODE(&self->rb_node);
	self->groups   = NULL;
	self->referenced = false;
	self->erange_warned = false;
}