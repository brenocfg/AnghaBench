#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ requirement; TYPE_2__* alternative; int /*<<< orphan*/  memrefs; } ;
typedef  TYPE_1__ rc_trigger_t ;
typedef  int /*<<< orphan*/  rc_peek_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
typedef  TYPE_2__ rc_condset_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  rc_reset_trigger (TYPE_1__*) ; 
 int rc_test_condset (TYPE_2__*,int*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_update_memref_values (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int rc_test_trigger(rc_trigger_t* self, rc_peek_t peek, void* ud, lua_State* L) {
  int ret, reset;
  rc_condset_t* condset;

  rc_update_memref_values(self->memrefs, peek, ud);

  reset = 0;
  ret = self->requirement != 0 ? rc_test_condset(self->requirement, &reset, peek, ud, L) : 1;
  condset = self->alternative;

  if (condset) {
    int sub = 0;

    do {
      sub |= rc_test_condset(condset, &reset, peek, ud, L);
      condset = condset->next;
    }
    while (condset != 0);

    ret &= sub && !reset;
  }

  if (reset) {
    rc_reset_trigger(self);
  }

  return ret;
}