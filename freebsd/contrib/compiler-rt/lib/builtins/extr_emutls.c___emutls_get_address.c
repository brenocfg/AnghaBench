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
struct TYPE_3__ {void** data; } ;
typedef  TYPE_1__ emutls_address_array ;
typedef  int /*<<< orphan*/  __emutls_control ;

/* Variables and functions */
 void* emutls_allocate_object (int /*<<< orphan*/ *) ; 
 TYPE_1__* emutls_get_address_array (int /*<<< orphan*/ ) ; 
 uintptr_t emutls_get_index (int /*<<< orphan*/ *) ; 

void *__emutls_get_address(__emutls_control *control) {
  uintptr_t index = emutls_get_index(control);
  emutls_address_array *array = emutls_get_address_array(index--);
  if (array->data[index] == NULL)
    array->data[index] = emutls_allocate_object(control);
  return array->data[index];
}