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
struct vmap_area {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct vmap_area* find_vmap_area (unsigned long) ; 
 int /*<<< orphan*/  free_unmap_vmap_area (struct vmap_area*) ; 

__attribute__((used)) static void free_unmap_vmap_area_addr(unsigned long addr)
{
	struct vmap_area *va;

	va = find_vmap_area(addr);
	BUG_ON(!va);
	free_unmap_vmap_area(va);
}