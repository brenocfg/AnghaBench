#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* kcdata_subtype_descriptor_t ;
struct TYPE_3__ {int kcs_elem_size; } ;

/* Variables and functions */

__attribute__((used)) static inline int
kcs_set_elem_size(kcdata_subtype_descriptor_t d, uint32_t size, uint32_t count)
{
	if (count > 1) {
		/* means we are setting up an array */
		if (size > 0xffff || count > 0xffff)
			return -1; //invalid argument
		d->kcs_elem_size = ((count & 0xffff) << 16 | (size & 0xffff));
	}
	else
	{
		d->kcs_elem_size = size;
	}
	return 0;
}