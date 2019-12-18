#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {uintptr_t size; scalar_t__ data; int /*<<< orphan*/  skip_destructor_rounds; } ;
typedef  TYPE_1__ emutls_address_array ;

/* Variables and functions */
 int /*<<< orphan*/  EMUTLS_SKIP_DESTRUCTOR_ROUNDS ; 
 int /*<<< orphan*/  emutls_asize (uintptr_t) ; 
 int /*<<< orphan*/  emutls_check_array_set_size (TYPE_1__*,uintptr_t) ; 
 TYPE_1__* emutls_getspecific () ; 
 uintptr_t emutls_new_data_array_size (uintptr_t) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,uintptr_t) ; 
 scalar_t__ realloc (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline emutls_address_array *
emutls_get_address_array(uintptr_t index) {
  emutls_address_array *array = emutls_getspecific();
  if (array == NULL) {
    uintptr_t new_size = emutls_new_data_array_size(index);
    array = (emutls_address_array *)malloc(emutls_asize(new_size));
    if (array) {
      memset(array->data, 0, new_size * sizeof(void *));
      array->skip_destructor_rounds = EMUTLS_SKIP_DESTRUCTOR_ROUNDS;
    }
    emutls_check_array_set_size(array, new_size);
  } else if (index > array->size) {
    uintptr_t orig_size = array->size;
    uintptr_t new_size = emutls_new_data_array_size(index);
    array = (emutls_address_array *)realloc(array, emutls_asize(new_size));
    if (array)
      memset(array->data + orig_size, 0,
             (new_size - orig_size) * sizeof(void *));
    emutls_check_array_set_size(array, new_size);
  }
  return array;
}