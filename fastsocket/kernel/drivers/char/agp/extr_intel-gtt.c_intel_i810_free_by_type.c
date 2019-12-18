#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {scalar_t__ type; int page_count; int /*<<< orphan*/ * pages; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* agp_destroy_page ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_PAGE_DESTROY_FREE ; 
 int /*<<< orphan*/  AGP_PAGE_DESTROY_UNMAP ; 
 scalar_t__ AGP_PHYS_MEMORY ; 
 TYPE_2__* agp_bridge ; 
 int /*<<< orphan*/  agp_free_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_page_array (struct agp_memory*) ; 
 int /*<<< orphan*/  i8xx_destroy_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct agp_memory*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_i810_free_by_type(struct agp_memory *curr)
{
	agp_free_key(curr->key);
	if (curr->type == AGP_PHYS_MEMORY) {
		if (curr->page_count == 4)
			i8xx_destroy_pages(curr->pages[0]);
		else {
			agp_bridge->driver->agp_destroy_page(curr->pages[0],
							     AGP_PAGE_DESTROY_UNMAP);
			agp_bridge->driver->agp_destroy_page(curr->pages[0],
							     AGP_PAGE_DESTROY_FREE);
		}
		agp_free_page_array(curr);
	}
	kfree(curr);
}