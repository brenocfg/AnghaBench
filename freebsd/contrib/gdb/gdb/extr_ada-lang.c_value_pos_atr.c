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
 scalar_t__ TYPE_CODE_ENUM ; 
 scalar_t__ TYPE_FIELD_BITPOS (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  builtin_type_ada_int ; 
 int /*<<< orphan*/  discrete_type_p (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int value_as_long (struct value*) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct value *
value_pos_atr (struct value *arg)
{
  struct type *type = VALUE_TYPE (arg);

  if (!discrete_type_p (type))
    error ("'POS only defined on discrete types");

  if (TYPE_CODE (type) == TYPE_CODE_ENUM)
    {
      int i;
      LONGEST v = value_as_long (arg);

      for (i = 0; i < TYPE_NFIELDS (type); i += 1)
	{
	  if (v == TYPE_FIELD_BITPOS (type, i))
	    return value_from_longest (builtin_type_ada_int, i);
	}
      error ("enumeration value is invalid: can't find 'POS");
    }
  else
    return value_from_longest (builtin_type_ada_int, value_as_long (arg));
}