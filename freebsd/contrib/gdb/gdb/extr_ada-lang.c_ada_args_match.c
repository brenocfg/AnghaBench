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
struct type {int dummy; } ;
struct symbol {int dummy; } ;

/* Variables and functions */
 scalar_t__ LOC_CONST ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ENUM ; 
 scalar_t__ TYPE_CODE_FUNC ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  ada_type_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ada_args_match (struct symbol *func, struct value **actuals, int n_actuals)
{
  int i;
  struct type *func_type = SYMBOL_TYPE (func);

  if (SYMBOL_CLASS (func) == LOC_CONST &&
      TYPE_CODE (func_type) == TYPE_CODE_ENUM)
    return (n_actuals == 0);
  else if (func_type == NULL || TYPE_CODE (func_type) != TYPE_CODE_FUNC)
    return 0;

  if (TYPE_NFIELDS (func_type) != n_actuals)
    return 0;

  for (i = 0; i < n_actuals; i += 1)
    {
      struct type *ftype = check_typedef (TYPE_FIELD_TYPE (func_type, i));
      struct type *atype = check_typedef (VALUE_TYPE (actuals[i]));

      if (!ada_type_match (TYPE_FIELD_TYPE (func_type, i),
			   VALUE_TYPE (actuals[i]), 1))
	return 0;
    }
  return 1;
}