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
struct flex_array_part {void* elements; } ;
struct flex_array {unsigned int total_nr_elements; struct flex_array_part** parts; } ;

/* Variables and functions */
 scalar_t__ elements_fit_in_base (struct flex_array*) ; 
 int fa_element_to_part_nr (struct flex_array*,unsigned int) ; 
 size_t index_inside_part (struct flex_array*,unsigned int) ; 

void *flex_array_get(struct flex_array *fa, unsigned int element_nr)
{
	int part_nr = fa_element_to_part_nr(fa, element_nr);
	struct flex_array_part *part;

	if (element_nr >= fa->total_nr_elements)
		return NULL;
	if (elements_fit_in_base(fa))
		part = (struct flex_array_part *)&fa->parts[0];
	else {
		part = fa->parts[part_nr];
		if (!part)
			return NULL;
	}
	return &part->elements[index_inside_part(fa, element_nr)];
}