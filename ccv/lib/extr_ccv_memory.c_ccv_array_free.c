#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; scalar_t__ sig; int size; int rsize; struct TYPE_5__* data; scalar_t__ refcount; } ;
typedef  TYPE_1__ ccv_array_t ;

/* Variables and functions */
 int CCV_REUSABLE ; 
 int /*<<< orphan*/  ccfree (TYPE_1__*) ; 
 int /*<<< orphan*/  ccv_cache ; 
 int /*<<< orphan*/  ccv_cache_opt ; 
 int /*<<< orphan*/  ccv_cache_put (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*,size_t,int) ; 

void ccv_array_free(ccv_array_t* array)
{
	if (!ccv_cache_opt || !(array->type & CCV_REUSABLE) || array->sig == 0)
	{
		array->refcount = 0;
		ccfree(array->data);
		ccfree(array);
	} else {
		size_t size = sizeof(ccv_array_t) + array->size * array->rsize;
		ccv_cache_put(&ccv_cache, array->sig, array, size, 1 /* type 1 */);
	}
}