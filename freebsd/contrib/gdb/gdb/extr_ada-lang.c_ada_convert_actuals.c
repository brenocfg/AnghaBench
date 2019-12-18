#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct value {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_FIELD_TYPE (int /*<<< orphan*/ ,int) ; 
 int TYPE_NFIELDS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct value* convert_actual (struct value*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ada_convert_actuals (struct value *func, int nargs, struct value *args[],
		     CORE_ADDR *sp)
{
  int i;

  if (TYPE_NFIELDS (VALUE_TYPE (func)) == 0
      || nargs != TYPE_NFIELDS (VALUE_TYPE (func)))
    return;

  for (i = 0; i < nargs; i += 1)
    args[i] =
      convert_actual (args[i], TYPE_FIELD_TYPE (VALUE_TYPE (func), i), sp);
}