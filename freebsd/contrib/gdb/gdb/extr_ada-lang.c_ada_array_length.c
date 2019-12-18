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
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 scalar_t__ ada_array_bound_from_type (struct type*,int,int,struct type**) ; 
 scalar_t__ ada_is_packed_array_type (struct type*) ; 
 scalar_t__ ada_is_simple_array (struct type*) ; 
 struct type* builtin_type_ada_int ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 struct value* decode_packed_array (struct value*) ; 
 int /*<<< orphan*/  desc_bounds (struct value*) ; 
 int /*<<< orphan*/  desc_one_bound (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ value_as_long (int /*<<< orphan*/ ) ; 
 struct value* value_from_longest (struct type*,scalar_t__) ; 

struct value *
ada_array_length (struct value *arr, int n)
{
  struct type *arr_type = check_typedef (VALUE_TYPE (arr));
  struct type *index_type_desc;

  if (ada_is_packed_array_type (arr_type))
    return ada_array_length (decode_packed_array (arr), n);

  if (ada_is_simple_array (arr_type))
    {
      struct type *type;
      LONGEST v =
	ada_array_bound_from_type (arr_type, n, 1, &type) -
	ada_array_bound_from_type (arr_type, n, 0, NULL) + 1;
      return value_from_longest (type, v);
    }
  else
    return
      value_from_longest (builtin_type_ada_int,
			  value_as_long (desc_one_bound (desc_bounds (arr),
							 n, 1))
			  - value_as_long (desc_one_bound (desc_bounds (arr),
							   n, 0)) + 1);
}