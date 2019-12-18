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
typedef  TYPE_1__* vector_upl_t ;
struct TYPE_8__ {int offset; int size; } ;
typedef  TYPE_2__ vector_upl_iostates_t ;
typedef  TYPE_3__* upl_t ;
typedef  int upl_size_t ;
typedef  int upl_offset_t ;
typedef  size_t uint32_t ;
struct TYPE_9__ {TYPE_1__* vector_upl; } ;
struct TYPE_7__ {size_t num_upls; TYPE_2__* upl_iostates; TYPE_3__** upl_elems; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vector_upl_is_valid (TYPE_3__*) ; 

upl_t
vector_upl_subupl_byoffset(upl_t upl, upl_offset_t *upl_offset, upl_size_t *upl_size)
{
	if(vector_upl_is_valid(upl)) {
		uint32_t i=0;
		vector_upl_t vector_upl = upl->vector_upl;

		if(vector_upl) {
			upl_t subupl = NULL;
			vector_upl_iostates_t subupl_state;

			for(i=0; i < vector_upl->num_upls; i++) {
				subupl = vector_upl->upl_elems[i];
				subupl_state = vector_upl->upl_iostates[i];
				if( *upl_offset <= (subupl_state.offset + subupl_state.size - 1)) {
					/* We could have been passed an offset/size pair that belongs
					 * to an UPL element that has already been committed/aborted.
					 * If so, return NULL.
					 */
					if(subupl == NULL)
						return NULL;
					if((subupl_state.offset + subupl_state.size) < (*upl_offset + *upl_size)) {
						*upl_size = (subupl_state.offset + subupl_state.size) - *upl_offset;
						if(*upl_size > subupl_state.size)
							*upl_size = subupl_state.size;
					}
					if(*upl_offset >= subupl_state.offset)
						*upl_offset -= subupl_state.offset;
					else if(i)
						panic("Vector UPL offset miscalculation\n");
					return subupl;
				}
			}
		}
		else
			panic("vector_upl_subupl_byoffset was passed a non-vectored UPL\n");
	}
	return NULL;
}