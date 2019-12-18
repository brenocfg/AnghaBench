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
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 int /*<<< orphan*/  TYPE_INDEX_TYPE (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  get_discrete_bounds (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  lookup_pointer_type (struct type*) ; 
 struct value* value_add (struct value*,struct value*) ; 
 struct value* value_cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_copy (struct value*) ; 
 int /*<<< orphan*/  value_from_longest (int /*<<< orphan*/ ,scalar_t__) ; 
 struct value* value_ind (struct value*) ; 
 struct value* value_sub (struct value*,int /*<<< orphan*/ ) ; 

struct value *
ada_value_ptr_subscript (struct value *arr, struct type *type, int arity,
			 struct value **ind)
{
  int k;

  for (k = 0; k < arity; k += 1)
    {
      LONGEST lwb, upb;
      struct value *idx;

      if (TYPE_CODE (type) != TYPE_CODE_ARRAY)
	error ("too many subscripts (%d expected)", k);
      arr = value_cast (lookup_pointer_type (TYPE_TARGET_TYPE (type)),
			value_copy (arr));
      get_discrete_bounds (TYPE_INDEX_TYPE (type), &lwb, &upb);
      if (lwb == 0)
	idx = ind[k];
      else
	idx = value_sub (ind[k], value_from_longest (builtin_type_int, lwb));
      arr = value_add (arr, idx);
      type = TYPE_TARGET_TYPE (type);
    }

  return value_ind (arr);
}