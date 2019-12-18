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
struct TYPE_3__ {uintptr_t size; scalar_t__* data; } ;
typedef  TYPE_1__ emutls_address_array ;

/* Variables and functions */
 int /*<<< orphan*/  emutls_memalign_free (scalar_t__) ; 

__attribute__((used)) static void emutls_shutdown(emutls_address_array *array) {
  if (array) {
    uintptr_t i;
    for (i = 0; i < array->size; ++i) {
      if (array->data[i])
        emutls_memalign_free(array->data[i]);
    }
  }
}