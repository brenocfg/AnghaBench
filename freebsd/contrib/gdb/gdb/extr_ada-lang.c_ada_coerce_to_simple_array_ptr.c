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
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 scalar_t__ ada_is_array_descriptor (int /*<<< orphan*/ ) ; 
 scalar_t__ ada_is_packed_array_type (int /*<<< orphan*/ ) ; 
 struct type* ada_type_of_array (struct value*,int) ; 
 struct value* decode_packed_array (struct value*) ; 
 int /*<<< orphan*/  desc_data (struct value*) ; 
 struct value* value_cast (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_copy (int /*<<< orphan*/ ) ; 

struct value *
ada_coerce_to_simple_array_ptr (struct value *arr)
{
  if (ada_is_array_descriptor (VALUE_TYPE (arr)))
    {
      struct type *arrType = ada_type_of_array (arr, 1);
      if (arrType == NULL)
	return NULL;
      return value_cast (arrType, value_copy (desc_data (arr)));
    }
  else if (ada_is_packed_array_type (VALUE_TYPE (arr)))
    return decode_packed_array (arr);
  else
    return arr;
}