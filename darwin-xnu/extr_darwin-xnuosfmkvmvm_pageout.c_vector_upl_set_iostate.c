#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vector_upl_t ;
typedef  TYPE_3__* upl_t ;
typedef  scalar_t__ upl_size_t ;
typedef  int /*<<< orphan*/  upl_offset_t ;
typedef  size_t uint32_t ;
struct TYPE_9__ {TYPE_2__* vector_upl; } ;
struct TYPE_8__ {size_t num_upls; TYPE_1__* upl_iostates; TYPE_3__** upl_elems; } ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vector_upl_is_valid (TYPE_3__*) ; 

void
vector_upl_set_iostate(upl_t upl, upl_t subupl, upl_offset_t offset, upl_size_t size)
{
	if(vector_upl_is_valid(upl)) {
		uint32_t i = 0;
		vector_upl_t vector_upl = upl->vector_upl;

		if(vector_upl) {
			for(i = 0; i < vector_upl->num_upls; i++) {
				if(vector_upl->upl_elems[i] == subupl)
					break;
			}

			if(i == vector_upl->num_upls)
				panic("setting sub-upl iostate when none exists");

			vector_upl->upl_iostates[i].offset = offset;
			if(size < PAGE_SIZE)
				size = PAGE_SIZE;
			vector_upl->upl_iostates[i].size = size;
		}
		else
			panic("vector_upl_set_iostate was passed a non-vectored UPL\n");
	}
	else
		panic("vector_upl_set_iostate was passed a NULL UPL\n");
}