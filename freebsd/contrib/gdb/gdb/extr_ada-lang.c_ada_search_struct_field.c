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
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 scalar_t__ ada_is_variant_part (struct type*,int) ; 
 scalar_t__ ada_is_wrapper_field (struct type*,int) ; 
 struct value* ada_value_primitive_field (struct value*,int,int,struct type*) ; 
 struct type* check_typedef (struct type*) ; 
 scalar_t__ field_name_match (char*,char*) ; 

struct value *
ada_search_struct_field (char *name, struct value *arg, int offset,
			 struct type *type)
{
  int i;
  CHECK_TYPEDEF (type);

  for (i = TYPE_NFIELDS (type) - 1; i >= 0; i -= 1)
    {
      char *t_field_name = TYPE_FIELD_NAME (type, i);

      if (t_field_name == NULL)
	continue;

      else if (field_name_match (t_field_name, name))
	return ada_value_primitive_field (arg, offset, i, type);

      else if (ada_is_wrapper_field (type, i))
	{
	  struct value *v = ada_search_struct_field (name, arg,
						     offset +
						     TYPE_FIELD_BITPOS (type,
									i) /
						     8,
						     TYPE_FIELD_TYPE (type,
								      i));
	  if (v != NULL)
	    return v;
	}

      else if (ada_is_variant_part (type, i))
	{
	  int j;
	  struct type *field_type = check_typedef (TYPE_FIELD_TYPE (type, i));
	  int var_offset = offset + TYPE_FIELD_BITPOS (type, i) / 8;

	  for (j = TYPE_NFIELDS (field_type) - 1; j >= 0; j -= 1)
	    {
	      struct value *v = ada_search_struct_field (name, arg,
							 var_offset
							 +
							 TYPE_FIELD_BITPOS
							 (field_type, j) / 8,
							 TYPE_FIELD_TYPE
							 (field_type, j));
	      if (v != NULL)
		return v;
	    }
	}
    }
  return NULL;
}