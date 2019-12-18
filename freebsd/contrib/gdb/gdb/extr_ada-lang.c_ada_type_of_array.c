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
struct objfile {int dummy; } ;

/* Variables and functions */
 struct objfile* TYPE_OBJFILE (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (int /*<<< orphan*/ ) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int ada_array_arity (struct type*) ; 
 struct type* ada_array_element_type (struct type*,int) ; 
 int /*<<< orphan*/  ada_is_array_descriptor (struct type*) ; 
 scalar_t__ ada_is_packed_array_type (struct type*) ; 
 struct type* alloc_type (struct objfile*) ; 
 struct type* check_typedef (struct type*) ; 
 struct type* create_array_type (struct type*,struct type*,struct type*) ; 
 int /*<<< orphan*/  create_range_type (struct type*,struct type*,int,int) ; 
 struct type* decode_packed_array_type (struct type*) ; 
 struct value* desc_bounds (struct value*) ; 
 int /*<<< orphan*/  desc_data_type (struct type*) ; 
 struct value* desc_one_bound (struct value*,int,int) ; 
 struct type* lookup_pointer_type (struct type*) ; 
 scalar_t__ value_as_long (struct value*) ; 

struct type *
ada_type_of_array (struct value *arr, int bounds)
{
  if (ada_is_packed_array_type (VALUE_TYPE (arr)))
    return decode_packed_array_type (VALUE_TYPE (arr));

  if (!ada_is_array_descriptor (VALUE_TYPE (arr)))
    return VALUE_TYPE (arr);

  if (!bounds)
    return
      check_typedef (TYPE_TARGET_TYPE (desc_data_type (VALUE_TYPE (arr))));
  else
    {
      struct type *elt_type;
      int arity;
      struct value *descriptor;
      struct objfile *objf = TYPE_OBJFILE (VALUE_TYPE (arr));

      elt_type = ada_array_element_type (VALUE_TYPE (arr), -1);
      arity = ada_array_arity (VALUE_TYPE (arr));

      if (elt_type == NULL || arity == 0)
	return check_typedef (VALUE_TYPE (arr));

      descriptor = desc_bounds (arr);
      if (value_as_long (descriptor) == 0)
	return NULL;
      while (arity > 0)
	{
	  struct type *range_type = alloc_type (objf);
	  struct type *array_type = alloc_type (objf);
	  struct value *low = desc_one_bound (descriptor, arity, 0);
	  struct value *high = desc_one_bound (descriptor, arity, 1);
	  arity -= 1;

	  create_range_type (range_type, VALUE_TYPE (low),
			     (int) value_as_long (low),
			     (int) value_as_long (high));
	  elt_type = create_array_type (array_type, elt_type, range_type);
	}

      return lookup_pointer_type (elt_type);
    }
}