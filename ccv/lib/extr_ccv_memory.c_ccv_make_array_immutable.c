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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {scalar_t__ sig; int size; int rsize; int /*<<< orphan*/  data; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_EOF_SIGN ; 
 int /*<<< orphan*/  CCV_REUSABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_cache_generate_signature (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ccv_make_array_immutable(ccv_array_t* array)
{
	assert(array->sig == 0);
	array->type &= ~CCV_REUSABLE;
	/* TODO: trim the array */
	array->sig = ccv_cache_generate_signature(array->data, array->size * array->rsize, (uint64_t)array->rsize, CCV_EOF_SIGN);
}