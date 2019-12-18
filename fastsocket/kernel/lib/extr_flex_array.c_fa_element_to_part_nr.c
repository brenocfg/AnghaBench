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
struct flex_array {int /*<<< orphan*/  element_size; } ;

/* Variables and functions */
 unsigned int FLEX_ARRAY_ELEMENTS_PER_PART (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fa_element_to_part_nr(struct flex_array *fa,
					unsigned int element_nr)
{
	return element_nr / FLEX_ARRAY_ELEMENTS_PER_PART(fa->element_size);
}