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
struct TYPE_4__ {uintptr_t size; } ;
typedef  TYPE_1__ emutls_address_array ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  emutls_setspecific (TYPE_1__*) ; 

__attribute__((used)) static __inline void emutls_check_array_set_size(emutls_address_array *array,
                                                 uintptr_t size) {
  if (array == NULL)
    abort();
  array->size = size;
  emutls_setspecific(array);
}