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
struct ati_page_map {int dummy; } ;
struct TYPE_2__ {int num_tables; struct ati_page_map** gatt_pages; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ati_create_page_map (struct ati_page_map*) ; 
 int /*<<< orphan*/  ati_free_gatt_pages () ; 
 TYPE_1__ ati_generic_private ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ati_create_gatt_pages(int nr_tables)
{
	struct ati_page_map **tables;
	struct ati_page_map *entry;
	int retval = 0;
	int i;

	tables = kzalloc((nr_tables + 1) * sizeof(struct ati_page_map *),GFP_KERNEL);
	if (tables == NULL)
		return -ENOMEM;

	for (i = 0; i < nr_tables; i++) {
		entry = kzalloc(sizeof(struct ati_page_map), GFP_KERNEL);
		tables[i] = entry;
		if (entry == NULL) {
			retval = -ENOMEM;
			break;
		}
		retval = ati_create_page_map(entry);
		if (retval != 0)
			break;
	}
	ati_generic_private.num_tables = i;
	ati_generic_private.gatt_pages = tables;

	if (retval != 0)
		ati_free_gatt_pages();

	return retval;
}