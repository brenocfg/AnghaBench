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
struct serverworks_page_map {scalar_t__ real; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  set_memory_wb (unsigned long,int) ; 

__attribute__((used)) static void serverworks_free_page_map(struct serverworks_page_map *page_map)
{
	set_memory_wb((unsigned long)page_map->real, 1);
	free_page((unsigned long) page_map->real);
}