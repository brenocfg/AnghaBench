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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/ * data; scalar_t__ capacity; } ;
typedef  TYPE_1__ KHRN_VECTOR_T ;

/* Variables and functions */
 int /*<<< orphan*/ * khrn_platform_malloc (scalar_t__,char*) ; 

void khrn_vector_init(KHRN_VECTOR_T *vector, uint32_t capacity)
{
   vector->data = (capacity == 0) ? NULL : khrn_platform_malloc(capacity, "KHRN_VECTOR_T.data");
   vector->capacity = vector->data ? capacity : 0;
   vector->size = 0;
}