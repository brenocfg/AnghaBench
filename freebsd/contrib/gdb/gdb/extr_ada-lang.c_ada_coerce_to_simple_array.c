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

/* Variables and functions */
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct value* ada_coerce_to_simple_array_ptr (struct value*) ; 
 scalar_t__ ada_is_array_descriptor (int /*<<< orphan*/ ) ; 
 scalar_t__ ada_is_packed_array_type (int /*<<< orphan*/ ) ; 
 struct value* decode_packed_array (struct value*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct value* value_ind (struct value*) ; 

struct value *
ada_coerce_to_simple_array (struct value *arr)
{
  if (ada_is_array_descriptor (VALUE_TYPE (arr)))
    {
      struct value *arrVal = ada_coerce_to_simple_array_ptr (arr);
      if (arrVal == NULL)
	error ("Bounds unavailable for null array pointer.");
      return value_ind (arrVal);
    }
  else if (ada_is_packed_array_type (VALUE_TYPE (arr)))
    return decode_packed_array (arr);
  else
    return arr;
}