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
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int /*<<< orphan*/  DOUBLEST ;

/* Variables and functions */
 struct type* VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  ada_fixed_to_float (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ada_float_to_fixed (struct type*,int /*<<< orphan*/ ) ; 
 scalar_t__ ada_is_fixed_point_type (struct type*) ; 
 int /*<<< orphan*/  builtin_type_double ; 
 int /*<<< orphan*/  value_as_double (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_as_long (struct value*) ; 
 int /*<<< orphan*/  value_cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_copy (struct value*) ; 
 struct value* value_from_longest (struct type*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct value *
cast_to_fixed (struct type *type, struct value *arg)
{
  LONGEST val;

  if (type == VALUE_TYPE (arg))
    return arg;
  else if (ada_is_fixed_point_type (VALUE_TYPE (arg)))
    val = ada_float_to_fixed (type,
			      ada_fixed_to_float (VALUE_TYPE (arg),
						  value_as_long (arg)));
  else
    {
      DOUBLEST argd =
	value_as_double (value_cast (builtin_type_double, value_copy (arg)));
      val = ada_float_to_fixed (type, argd);
    }

  return value_from_longest (type, val);
}