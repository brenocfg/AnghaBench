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
typedef  int /*<<< orphan*/  rc_peek_t ;
struct TYPE_3__ {scalar_t__ previous; scalar_t__ value; scalar_t__ prior; struct TYPE_3__* next; int /*<<< orphan*/  memref; } ;
typedef  TYPE_1__ rc_memref_value_t ;

/* Variables and functions */
 scalar_t__ rc_memref_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

void rc_update_memref_values(rc_memref_value_t* memref, rc_peek_t peek, void* ud) {
  while (memref) {
    memref->previous = memref->value;
    memref->value = rc_memref_get_value(&memref->memref, peek, ud);
    if (memref->value != memref->previous)
      memref->prior = memref->previous;

    memref = memref->next;
  }
}