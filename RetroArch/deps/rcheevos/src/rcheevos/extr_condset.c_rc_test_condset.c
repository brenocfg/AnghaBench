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
typedef  int /*<<< orphan*/  rc_peek_t ;
struct TYPE_4__ {scalar_t__ conditions; scalar_t__ has_pause; } ;
typedef  TYPE_1__ rc_condset_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int rc_test_condset_internal (TYPE_1__*,int,int*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

int rc_test_condset(rc_condset_t* self, int* reset, rc_peek_t peek, void* ud, lua_State* L) {
  if (self->conditions == 0) {
    /* important: empty group must evaluate true */
    return 1;
  }

  if (self->has_pause && rc_test_condset_internal(self, 1, reset, peek, ud, L)) {
    /* one or more Pause conditions exists, if any of them are true, stop processing this group */
    return 0;
  }

  return rc_test_condset_internal(self, 0, reset, peek, ud, L);
}