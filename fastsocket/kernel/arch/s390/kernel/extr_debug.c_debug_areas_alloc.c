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
typedef  int /*<<< orphan*/ ************************ debug_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ***************************) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ************************************* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static debug_entry_t***
debug_areas_alloc(int pages_per_area, int nr_areas)
{
	debug_entry_t*** areas;
	int i,j;

	areas = kmalloc(nr_areas *
					sizeof(debug_entry_t**),
					GFP_KERNEL);
	if (!areas)
		goto fail_malloc_areas;
	for (i = 0; i < nr_areas; i++) {
		areas[i] = kmalloc(pages_per_area *
				sizeof(debug_entry_t*),GFP_KERNEL);
		if (!areas[i]) {
			goto fail_malloc_areas2;
		}
		for(j = 0; j < pages_per_area; j++) {
			areas[i][j] = kzalloc(PAGE_SIZE, GFP_KERNEL);
			if(!areas[i][j]) {
				for(j--; j >=0 ; j--) {
					kfree(areas[i][j]);
				}
				kfree(areas[i]);
				goto fail_malloc_areas2;
			}
		}
	}
	return areas;

fail_malloc_areas2:
	for(i--; i >= 0; i--){
		for(j=0; j < pages_per_area;j++){
			kfree(areas[i][j]);
		}
		kfree(areas[i]);
	}
	kfree(areas);
fail_malloc_areas:
	return NULL;

}