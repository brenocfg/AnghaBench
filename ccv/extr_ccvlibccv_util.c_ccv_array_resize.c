#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; int rnum; scalar_t__ rsize; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccrealloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ccv_array_get (TYPE_1__*,int) ; 
 int ccv_max (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

void ccv_array_resize(ccv_array_t* array, int rnum)
{
	if (rnum > array->size)
	{
		array->size = ccv_max(array->size * 3 / 2, rnum);
		array->data = ccrealloc(array->data, (size_t)array->size * (size_t)array->rsize);
	}
	memset(ccv_array_get(array, array->rnum), 0, (size_t)array->rsize * (size_t)(rnum - array->rnum));
	array->rnum = rnum;
}