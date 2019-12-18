#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cxx_scope ;
struct TYPE_5__ {int /*<<< orphan*/ * scope; struct TYPE_5__* previous; } ;
typedef  TYPE_1__ cxx_binding ;

/* Variables and functions */
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline cxx_binding *
find_binding (cxx_scope *scope, cxx_binding *binding)
{
  timevar_push (TV_NAME_LOOKUP);

  for (; binding != NULL; binding = binding->previous)
    if (binding->scope == scope)
      POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, binding);

  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, (cxx_binding *)0);
}