#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_offset_t ;
typedef  TYPE_2__* vector_upl_t ;
typedef  TYPE_3__* upl_t ;
struct _vector_upl {int dummy; } ;
struct TYPE_8__ {void* offset; TYPE_2__* vector_upl; } ;
struct TYPE_7__ {TYPE_1__* upl_iostates; int /*<<< orphan*/ * pagelist; scalar_t__ num_upls; scalar_t__ invalid_upls; void* offset; scalar_t__ size; } ;
struct TYPE_6__ {scalar_t__ offset; scalar_t__ size; } ;

/* Variables and functions */
 int MAX_VECTOR_UPL_ELEMENTS ; 
 int /*<<< orphan*/  UPL_VECTOR ; 
 int /*<<< orphan*/  kalloc (int) ; 
 TYPE_3__* upl_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

upl_t
vector_upl_create(vm_offset_t upl_offset)
{
	int	vector_upl_size  = sizeof(struct _vector_upl);
	int i=0;
	upl_t	upl;
	vector_upl_t vector_upl = (vector_upl_t)kalloc(vector_upl_size);

	upl = upl_create(0,UPL_VECTOR,0);
	upl->vector_upl = vector_upl;
	upl->offset = upl_offset;
	vector_upl->size = 0;
	vector_upl->offset = upl_offset;
	vector_upl->invalid_upls=0;
	vector_upl->num_upls=0;
	vector_upl->pagelist = NULL;

	for(i=0; i < MAX_VECTOR_UPL_ELEMENTS ; i++) {
		vector_upl->upl_iostates[i].size = 0;
		vector_upl->upl_iostates[i].offset = 0;

	}
	return upl;
}