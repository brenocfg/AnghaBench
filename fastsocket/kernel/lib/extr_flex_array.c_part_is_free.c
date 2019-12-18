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
struct flex_array_part {scalar_t__* elements; } ;

/* Variables and functions */
 scalar_t__ FLEX_ARRAY_FREE ; 

__attribute__((used)) static int part_is_free(struct flex_array_part *part)
{
	int i;

	for (i = 0; i < sizeof(struct flex_array_part); i++)
		if (part->elements[i] != FLEX_ARRAY_FREE)
			return 0;
	return 1;
}