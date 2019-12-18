#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  TYPE_1__* vector_upl_t ;
typedef  TYPE_2__* upl_t ;
typedef  scalar_t__ upl_page_info_array_t ;
typedef  size_t uint32_t ;
struct upl_page_info {int dummy; } ;
struct TYPE_8__ {int size; scalar_t__ highest_page; } ;
struct TYPE_7__ {scalar_t__ highest_page; TYPE_1__* vector_upl; } ;
struct TYPE_6__ {int size; size_t num_upls; TYPE_5__** upl_elems; scalar_t__ pagelist; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  UPL_GET_INTERNAL_PAGE_LIST_SIMPLE (TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ vector_upl_is_valid (TYPE_2__*) ; 

void
vector_upl_set_pagelist(upl_t upl)
{
	if(vector_upl_is_valid(upl)) {
		uint32_t i=0;
		vector_upl_t vector_upl = upl->vector_upl;

		if(vector_upl) {
			vm_offset_t pagelist_size=0, cur_upl_pagelist_size=0;

			vector_upl->pagelist = (upl_page_info_array_t)kalloc(sizeof(struct upl_page_info)*(vector_upl->size/PAGE_SIZE));

			for(i=0; i < vector_upl->num_upls; i++) {
				cur_upl_pagelist_size = sizeof(struct upl_page_info) * vector_upl->upl_elems[i]->size/PAGE_SIZE;
				bcopy(UPL_GET_INTERNAL_PAGE_LIST_SIMPLE(vector_upl->upl_elems[i]), (char*)vector_upl->pagelist + pagelist_size, cur_upl_pagelist_size);
				pagelist_size += cur_upl_pagelist_size;
				if(vector_upl->upl_elems[i]->highest_page > upl->highest_page)
					upl->highest_page = vector_upl->upl_elems[i]->highest_page;
			}
			assert( pagelist_size == (sizeof(struct upl_page_info)*(vector_upl->size/PAGE_SIZE)) );
		}
		else
			panic("vector_upl_set_pagelist was passed a non-vectored upl\n");
	}
	else
		panic("vector_upl_set_pagelist was passed a NULL upl\n");

}