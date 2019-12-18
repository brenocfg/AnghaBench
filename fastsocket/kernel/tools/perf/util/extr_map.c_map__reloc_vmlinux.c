#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct map {scalar_t__ pgoff; int /*<<< orphan*/  unmap_ip; int /*<<< orphan*/  map_ip; } ;
struct kmap {TYPE_1__* ref_reloc_sym; } ;
typedef  scalar_t__ s64 ;
struct TYPE_2__ {scalar_t__ addr; scalar_t__ unrelocated_addr; } ;

/* Variables and functions */
 struct kmap* map__kmap (struct map*) ; 
 int /*<<< orphan*/  map__reloc_map_ip ; 
 int /*<<< orphan*/  map__reloc_unmap_ip ; 

void map__reloc_vmlinux(struct map *self)
{
	struct kmap *kmap = map__kmap(self);
	s64 reloc;

	if (!kmap->ref_reloc_sym || !kmap->ref_reloc_sym->unrelocated_addr)
		return;

	reloc = (kmap->ref_reloc_sym->unrelocated_addr -
		 kmap->ref_reloc_sym->addr);

	if (!reloc)
		return;

	self->map_ip   = map__reloc_map_ip;
	self->unmap_ip = map__reloc_unmap_ip;
	self->pgoff    = reloc;
}