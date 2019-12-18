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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_REF ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 scalar_t__ ada_is_variant_part (struct type*,int) ; 
 scalar_t__ ada_is_wrapper_field (struct type*,int) ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ field_name_match (char*,char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  target_terminal_ours () ; 
 struct type* to_static_fixed_type (struct type*) ; 
 int /*<<< orphan*/  type_print (struct type*,char*,int /*<<< orphan*/ ,int) ; 

struct type *
ada_lookup_struct_elt_type (struct type *type, char *name, int noerr,
			    int *dispp)
{
  int i;

  if (name == NULL)
    goto BadName;

  while (1)
    {
      CHECK_TYPEDEF (type);
      if (TYPE_CODE (type) != TYPE_CODE_PTR
	  && TYPE_CODE (type) != TYPE_CODE_REF)
	break;
      type = TYPE_TARGET_TYPE (type);
    }

  if (TYPE_CODE (type) != TYPE_CODE_STRUCT &&
      TYPE_CODE (type) != TYPE_CODE_UNION)
    {
      target_terminal_ours ();
      gdb_flush (gdb_stdout);
      fprintf_unfiltered (gdb_stderr, "Type ");
      type_print (type, "", gdb_stderr, -1);
      error (" is not a structure or union type");
    }

  type = to_static_fixed_type (type);

  for (i = 0; i < TYPE_NFIELDS (type); i += 1)
    {
      char *t_field_name = TYPE_FIELD_NAME (type, i);
      struct type *t;
      int disp;

      if (t_field_name == NULL)
	continue;

      else if (field_name_match (t_field_name, name))
	{
	  if (dispp != NULL)
	    *dispp += TYPE_FIELD_BITPOS (type, i) / 8;
	  return check_typedef (TYPE_FIELD_TYPE (type, i));
	}

      else if (ada_is_wrapper_field (type, i))
	{
	  disp = 0;
	  t = ada_lookup_struct_elt_type (TYPE_FIELD_TYPE (type, i), name,
					  1, &disp);
	  if (t != NULL)
	    {
	      if (dispp != NULL)
		*dispp += disp + TYPE_FIELD_BITPOS (type, i) / 8;
	      return t;
	    }
	}

      else if (ada_is_variant_part (type, i))
	{
	  int j;
	  struct type *field_type = check_typedef (TYPE_FIELD_TYPE (type, i));

	  for (j = TYPE_NFIELDS (field_type) - 1; j >= 0; j -= 1)
	    {
	      disp = 0;
	      t = ada_lookup_struct_elt_type (TYPE_FIELD_TYPE (field_type, j),
					      name, 1, &disp);
	      if (t != NULL)
		{
		  if (dispp != NULL)
		    *dispp += disp + TYPE_FIELD_BITPOS (type, i) / 8;
		  return t;
		}
	    }
	}

    }

BadName:
  if (!noerr)
    {
      target_terminal_ours ();
      gdb_flush (gdb_stdout);
      fprintf_unfiltered (gdb_stderr, "Type ");
      type_print (type, "", gdb_stderr, -1);
      fprintf_unfiltered (gdb_stderr, " has no component named ");
      error ("%s", name == NULL ? "<null>" : name);
    }

  return NULL;
}