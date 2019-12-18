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
 int /*<<< orphan*/  TYPE_FIELD_NAME (struct type*,int) ; 
 struct type* TYPE_INDEX_TYPE (struct type*) ; 
 scalar_t__ TYPE_LENGTH (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  TYPE_OBJFILE (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 struct type* ada_find_parallel_type (struct type*,char*) ; 
 struct type* ada_to_fixed_type (struct type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct value*) ; 
 int /*<<< orphan*/  alloc_type (int /*<<< orphan*/ ) ; 
 struct type* check_typedef (struct type*) ; 
 struct type* create_array_type (int /*<<< orphan*/ ,struct type*,struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct type* to_fixed_range_type (int /*<<< orphan*/ ,struct value*,int /*<<< orphan*/ ) ; 
 scalar_t__ varsize_limit ; 

__attribute__((used)) static struct type *
to_fixed_array_type (struct type *type0, struct value *dval,
		     int ignore_too_big)
{
  struct type *index_type_desc;
  struct type *result;

  /* FIXME:  TYPE_FLAG_FIXED_INSTANCE should be defined in gdbtypes.h */
/*  if (ada_is_packed_array_type (type0)  /* revisit? *//*
   || (TYPE_FLAGS (type0) & TYPE_FLAG_FIXED_INSTANCE))
   return type0; */

  index_type_desc = ada_find_parallel_type (type0, "___XA");
  if (index_type_desc == NULL)
    {
      struct type *elt_type0 = check_typedef (TYPE_TARGET_TYPE (type0));
      /* NOTE: elt_type---the fixed version of elt_type0---should never
       * depend on the contents of the array in properly constructed
       * debugging data. */
      struct type *elt_type = ada_to_fixed_type (elt_type0, 0, 0, dval);

      if (elt_type0 == elt_type)
	result = type0;
      else
	result = create_array_type (alloc_type (TYPE_OBJFILE (type0)),
				    elt_type, TYPE_INDEX_TYPE (type0));
    }
  else
    {
      int i;
      struct type *elt_type0;

      elt_type0 = type0;
      for (i = TYPE_NFIELDS (index_type_desc); i > 0; i -= 1)
	elt_type0 = TYPE_TARGET_TYPE (elt_type0);

      /* NOTE: result---the fixed version of elt_type0---should never
       * depend on the contents of the array in properly constructed
       * debugging data. */
      result = ada_to_fixed_type (check_typedef (elt_type0), 0, 0, dval);
      for (i = TYPE_NFIELDS (index_type_desc) - 1; i >= 0; i -= 1)
	{
	  struct type *range_type =
	    to_fixed_range_type (TYPE_FIELD_NAME (index_type_desc, i),
				 dval, TYPE_OBJFILE (type0));
	  result = create_array_type (alloc_type (TYPE_OBJFILE (type0)),
				      result, range_type);
	}
      if (!ignore_too_big && TYPE_LENGTH (result) > varsize_limit)
	error ("array type with dynamic size is larger than varsize-limit");
    }

/* FIXME:  TYPE_FLAG_FIXED_INSTANCE should be defined in gdbtypes.h */
/*  TYPE_FLAGS (result) |= TYPE_FLAG_FIXED_INSTANCE; */
  return result;
}