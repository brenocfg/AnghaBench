#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ rc_term_t ;
typedef  int /*<<< orphan*/  rc_peek_t ;
struct TYPE_6__ {TYPE_1__* terms; } ;
typedef  TYPE_2__ rc_expression_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ rc_evaluate_term (TYPE_1__*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

unsigned rc_evaluate_expression(rc_expression_t* self, rc_peek_t peek, void* ud, lua_State* L) {
  rc_term_t* term;
  unsigned value;

  value = 0;

  for (term = self->terms; term != 0; term = term->next) {
    value += rc_evaluate_term(term, peek, ud, L);
  }

  return value;
}