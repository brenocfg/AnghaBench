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
struct vmap_area {int va_end; int va_start; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_LAZY_FREE ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ lazy_max_pages () ; 
 int /*<<< orphan*/  try_purge_vmap_area_lazy () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmap_lazy_nr ; 

__attribute__((used)) static void free_vmap_area_noflush(struct vmap_area *va)
{
	va->flags |= VM_LAZY_FREE;
	atomic_add((va->va_end - va->va_start) >> PAGE_SHIFT, &vmap_lazy_nr);
	if (unlikely(atomic_read(&vmap_lazy_nr) > lazy_max_pages()))
		try_purge_vmap_area_lazy();
}