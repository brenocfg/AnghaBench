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
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_LENGTH (struct type*) ; 
 scalar_t__ VALUE_ADDRESS (struct value*) ; 
 scalar_t__ VALUE_OFFSET (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 struct type* desc_bounds_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ is_thick_pntr (struct type*) ; 
 scalar_t__ is_thin_pntr (struct type*) ; 
 int /*<<< orphan*/  lookup_pointer_type (struct type*) ; 
 int /*<<< orphan*/  thin_descriptor_type (struct type*) ; 
 scalar_t__ value_as_long (struct value*) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,scalar_t__) ; 
 struct value* value_struct_elt (struct value**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static struct value *
desc_bounds (struct value *arr)
{
  struct type *type = check_typedef (VALUE_TYPE (arr));
  if (is_thin_pntr (type))
    {
      struct type *bounds_type =
	desc_bounds_type (thin_descriptor_type (type));
      LONGEST addr;

      if (desc_bounds_type == NULL)
	error ("Bad GNAT array descriptor");

      /* NOTE: The following calculation is not really kosher, but
         since desc_type is an XVE-encoded type (and shouldn't be),
         the correct calculation is a real pain. FIXME (and fix GCC). */
      if (TYPE_CODE (type) == TYPE_CODE_PTR)
	addr = value_as_long (arr);
      else
	addr = VALUE_ADDRESS (arr) + VALUE_OFFSET (arr);

      return
	value_from_longest (lookup_pointer_type (bounds_type),
			    addr - TYPE_LENGTH (bounds_type));
    }

  else if (is_thick_pntr (type))
    return value_struct_elt (&arr, NULL, "P_BOUNDS", NULL,
			     "Bad GNAT array descriptor");
  else
    return NULL;
}