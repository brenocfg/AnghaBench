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
struct flex_array_part {int dummy; } ;
struct flex_array {struct flex_array_part** parts; int /*<<< orphan*/  total_nr_elements; } ;

/* Variables and functions */
 int FLEX_ARRAY_NR_BASE_PTRS ; 
 scalar_t__ elements_fit_in_base (struct flex_array*) ; 
 int /*<<< orphan*/  kfree (struct flex_array_part*) ; 
 scalar_t__ part_is_free (struct flex_array_part*) ; 

int flex_array_shrink(struct flex_array *fa)
{
	struct flex_array_part *part;
	int part_nr;
	int ret = 0;

	if (!fa->total_nr_elements)
		return 0;
	if (elements_fit_in_base(fa))
		return ret;
	for (part_nr = 0; part_nr < FLEX_ARRAY_NR_BASE_PTRS; part_nr++) {
		part = fa->parts[part_nr];
		if (!part)
			continue;
		if (part_is_free(part)) {
			fa->parts[part_nr] = NULL;
			kfree(part);
			ret++;
		}
	}
	return ret;
}