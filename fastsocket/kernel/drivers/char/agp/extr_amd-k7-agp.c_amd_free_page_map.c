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
struct amd_page_map {scalar_t__ real; int /*<<< orphan*/  remapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_memory_wb (unsigned long,int) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 

__attribute__((used)) static void amd_free_page_map(struct amd_page_map *page_map)
{
#ifndef CONFIG_X86
	iounmap(page_map->remapped);
	ClearPageReserved(virt_to_page(page_map->real));
#else
	set_memory_wb((unsigned long)page_map->real, 1);
#endif
	free_page((unsigned long) page_map->real);
}