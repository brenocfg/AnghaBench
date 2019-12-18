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

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_FIELD_BITSIZE (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct value* ada_coerce_to_simple_array (struct value*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  value_pos_atr (struct value*) ; 
 struct value* value_subscript (struct value*,int /*<<< orphan*/ ) ; 
 struct value* value_subscript_packed (struct value*,int,struct value**) ; 

struct value *
ada_value_subscript (struct value *arr, int arity, struct value **ind)
{
  int k;
  struct value *elt;
  struct type *elt_type;

  elt = ada_coerce_to_simple_array (arr);

  elt_type = check_typedef (VALUE_TYPE (elt));
  if (TYPE_CODE (elt_type) == TYPE_CODE_ARRAY
      && TYPE_FIELD_BITSIZE (elt_type, 0) > 0)
    return value_subscript_packed (elt, arity, ind);

  for (k = 0; k < arity; k += 1)
    {
      if (TYPE_CODE (elt_type) != TYPE_CODE_ARRAY)
	error ("too many subscripts (%d expected)", k);
      elt = value_subscript (elt, value_pos_atr (ind[k]));
    }
  return elt;
}