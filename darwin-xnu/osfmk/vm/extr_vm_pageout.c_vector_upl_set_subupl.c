#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vector_upl_t ;
typedef  TYPE_2__* upl_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  size; TYPE_1__* vector_upl; } ;
struct TYPE_6__ {scalar_t__ num_upls; int /*<<< orphan*/  invalid_upls; TYPE_2__** upl_elems; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ hw_atomic_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vector_upl_is_valid (TYPE_2__*) ; 

boolean_t
vector_upl_set_subupl(upl_t upl,upl_t subupl, uint32_t io_size)
{
	if(vector_upl_is_valid(upl)) {
		vector_upl_t vector_upl = upl->vector_upl;

		if(vector_upl) {
			if(subupl) {
				if(io_size) {
					if(io_size < PAGE_SIZE)
						io_size = PAGE_SIZE;
					subupl->vector_upl = (void*)vector_upl;
					vector_upl->upl_elems[vector_upl->num_upls++] = subupl;
					vector_upl->size += io_size;
					upl->size += io_size;
				}
				else {
					uint32_t i=0,invalid_upls=0;
					for(i = 0; i < vector_upl->num_upls; i++) {
						if(vector_upl->upl_elems[i] == subupl)
							break;
					}
					if(i == vector_upl->num_upls)
						panic("Trying to remove sub-upl when none exists");

					vector_upl->upl_elems[i] = NULL;
					invalid_upls = hw_atomic_add(&(vector_upl)->invalid_upls, 1);
					if(invalid_upls == vector_upl->num_upls)
						return TRUE;
					else
						return FALSE;
				}
			}
			else
				panic("vector_upl_set_subupl was passed a NULL upl element\n");
		}
		else
			panic("vector_upl_set_subupl was passed a non-vectored upl\n");
	}
	else
		panic("vector_upl_set_subupl was passed a NULL upl\n");

	return FALSE;
}