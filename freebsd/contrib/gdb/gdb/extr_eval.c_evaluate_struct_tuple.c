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
struct expression {int dummy; } ;
typedef  enum noside { ____Placeholder_noside } noside ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQ (char*,char*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 int TYPE_FIELD_BITSIZE (struct type*,int) ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct value* evaluate_subexp (struct type*,struct expression*,int*,int) ; 
 char* get_label (struct expression*,int*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modify_field (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  value_as_long (struct value*) ; 
 struct value* value_cast (struct type*,struct value*) ; 

__attribute__((used)) static struct value *
evaluate_struct_tuple (struct value *struct_val,
		       struct expression *exp,
		       int *pos, enum noside noside, int nargs)
{
  struct type *struct_type = check_typedef (VALUE_TYPE (struct_val));
  struct type *substruct_type = struct_type;
  struct type *field_type;
  int fieldno = -1;
  int variantno = -1;
  int subfieldno = -1;
  while (--nargs >= 0)
    {
      int pc = *pos;
      struct value *val = NULL;
      int nlabels = 0;
      int bitpos, bitsize;
      char *addr;

      /* Skip past the labels, and count them. */
      while (get_label (exp, pos) != NULL)
	nlabels++;

      do
	{
	  char *label = get_label (exp, &pc);
	  if (label)
	    {
	      for (fieldno = 0; fieldno < TYPE_NFIELDS (struct_type);
		   fieldno++)
		{
		  char *field_name = TYPE_FIELD_NAME (struct_type, fieldno);
		  if (field_name != NULL && DEPRECATED_STREQ (field_name, label))
		    {
		      variantno = -1;
		      subfieldno = fieldno;
		      substruct_type = struct_type;
		      goto found;
		    }
		}
	      for (fieldno = 0; fieldno < TYPE_NFIELDS (struct_type);
		   fieldno++)
		{
		  char *field_name = TYPE_FIELD_NAME (struct_type, fieldno);
		  field_type = TYPE_FIELD_TYPE (struct_type, fieldno);
		  if ((field_name == 0 || *field_name == '\0')
		      && TYPE_CODE (field_type) == TYPE_CODE_UNION)
		    {
		      variantno = 0;
		      for (; variantno < TYPE_NFIELDS (field_type);
			   variantno++)
			{
			  substruct_type
			    = TYPE_FIELD_TYPE (field_type, variantno);
			  if (TYPE_CODE (substruct_type) == TYPE_CODE_STRUCT)
			    {
			      for (subfieldno = 0;
				 subfieldno < TYPE_NFIELDS (substruct_type);
				   subfieldno++)
				{
				  if (DEPRECATED_STREQ (TYPE_FIELD_NAME (substruct_type,
							      subfieldno),
					     label))
				    {
				      goto found;
				    }
				}
			    }
			}
		    }
		}
	      error ("there is no field named %s", label);
	    found:
	      ;
	    }
	  else
	    {
	      /* Unlabelled tuple element - go to next field. */
	      if (variantno >= 0)
		{
		  subfieldno++;
		  if (subfieldno >= TYPE_NFIELDS (substruct_type))
		    {
		      variantno = -1;
		      substruct_type = struct_type;
		    }
		}
	      if (variantno < 0)
		{
		  fieldno++;
		  subfieldno = fieldno;
		  if (fieldno >= TYPE_NFIELDS (struct_type))
		    error ("too many initializers");
		  field_type = TYPE_FIELD_TYPE (struct_type, fieldno);
		  if (TYPE_CODE (field_type) == TYPE_CODE_UNION
		      && TYPE_FIELD_NAME (struct_type, fieldno)[0] == '0')
		    error ("don't know which variant you want to set");
		}
	    }

	  /* Here, struct_type is the type of the inner struct,
	     while substruct_type is the type of the inner struct.
	     These are the same for normal structures, but a variant struct
	     contains anonymous union fields that contain substruct fields.
	     The value fieldno is the index of the top-level (normal or
	     anonymous union) field in struct_field, while the value
	     subfieldno is the index of the actual real (named inner) field
	     in substruct_type. */

	  field_type = TYPE_FIELD_TYPE (substruct_type, subfieldno);
	  if (val == 0)
	    val = evaluate_subexp (field_type, exp, pos, noside);

	  /* Now actually set the field in struct_val. */

	  /* Assign val to field fieldno. */
	  if (VALUE_TYPE (val) != field_type)
	    val = value_cast (field_type, val);

	  bitsize = TYPE_FIELD_BITSIZE (substruct_type, subfieldno);
	  bitpos = TYPE_FIELD_BITPOS (struct_type, fieldno);
	  if (variantno >= 0)
	    bitpos += TYPE_FIELD_BITPOS (substruct_type, subfieldno);
	  addr = VALUE_CONTENTS (struct_val) + bitpos / 8;
	  if (bitsize)
	    modify_field (addr, value_as_long (val),
			  bitpos % 8, bitsize);
	  else
	    memcpy (addr, VALUE_CONTENTS (val),
		    TYPE_LENGTH (VALUE_TYPE (val)));
	}
      while (--nlabels > 0);
    }
  return struct_val;
}