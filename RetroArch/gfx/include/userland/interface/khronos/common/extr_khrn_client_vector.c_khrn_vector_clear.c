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
struct TYPE_3__ {scalar_t__ size; scalar_t__ capacity; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ KHRN_VECTOR_T ;

/* Variables and functions */
 int /*<<< orphan*/  khrn_platform_free (int /*<<< orphan*/ *) ; 

void khrn_vector_clear(KHRN_VECTOR_T *vector)
{
   if (vector->data) {
      khrn_platform_free(vector->data);
   }
   vector->data = NULL;
   vector->capacity = 0;
   vector->size = 0;
}