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
typedef  scalar_t__ tree ;
struct c_declspecs {scalar_t__ type; scalar_t__ storage_class; scalar_t__ restrict_p; scalar_t__ volatile_p; scalar_t__ const_p; scalar_t__ thread_p; scalar_t__ inline_p; scalar_t__ typedef_p; int /*<<< orphan*/  tag_defined_p; int /*<<< orphan*/  default_int_p; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int ENUMERAL_TYPE ; 
 int RECORD_TYPE ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_NAME (scalar_t__) ; 
 int UNION_TYPE ; 
 scalar_t__ csc_auto ; 
 scalar_t__ csc_none ; 
 scalar_t__ csc_register ; 
 scalar_t__ current_scope ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ file_scope ; 
 int /*<<< orphan*/  in_system_header ; 
 scalar_t__ lookup_tag (int,scalar_t__,int) ; 
 scalar_t__ make_node (int) ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 scalar_t__ pending_invalid_xref ; 
 int /*<<< orphan*/  pending_xref_error () ; 
 int /*<<< orphan*/  pushtag (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

void
shadow_tag_warned (const struct c_declspecs *declspecs, int warned)
{
  bool found_tag = false;

  if (declspecs->type && !declspecs->default_int_p && !declspecs->typedef_p)
    {
      tree value = declspecs->type;
      enum tree_code code = TREE_CODE (value);

      if (code == RECORD_TYPE || code == UNION_TYPE || code == ENUMERAL_TYPE)
	/* Used to test also that TYPE_SIZE (value) != 0.
	   That caused warning for `struct foo;' at top level in the file.  */
	{
	  tree name = TYPE_NAME (value);
	  tree t;

	  found_tag = true;

	  if (name == 0)
	    {
	      if (warned != 1 && code != ENUMERAL_TYPE)
		/* Empty unnamed enum OK */
		{
		  pedwarn ("unnamed struct/union that defines no instances");
		  warned = 1;
		}
	    }
	  else if (!declspecs->tag_defined_p
		   && declspecs->storage_class != csc_none)
	    {
	      if (warned != 1)
		pedwarn ("empty declaration with storage class specifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  else if (!declspecs->tag_defined_p
		   && (declspecs->const_p
		       || declspecs->volatile_p
		       || declspecs->restrict_p))
	    {
	      if (warned != 1)
		pedwarn ("empty declaration with type qualifier "
			 "does not redeclare tag");
	      warned = 1;
	      pending_xref_error ();
	    }
	  else
	    {
	      pending_invalid_xref = 0;
	      t = lookup_tag (code, name, 1);

	      if (t == 0)
		{
		  t = make_node (code);
		  pushtag (name, t);
		}
	    }
	}
      else
	{
	  if (warned != 1 && !in_system_header)
	    {
	      pedwarn ("useless type name in empty declaration");
	      warned = 1;
	    }
	}
    }
  else if (warned != 1 && !in_system_header && declspecs->typedef_p)
    {
      pedwarn ("useless type name in empty declaration");
      warned = 1;
    }

  pending_invalid_xref = 0;

  if (declspecs->inline_p)
    {
      error ("%<inline%> in empty declaration");
      warned = 1;
    }

  if (current_scope == file_scope && declspecs->storage_class == csc_auto)
    {
      error ("%<auto%> in file-scope empty declaration");
      warned = 1;
    }

  if (current_scope == file_scope && declspecs->storage_class == csc_register)
    {
      error ("%<register%> in file-scope empty declaration");
      warned = 1;
    }

  if (!warned && !in_system_header && declspecs->storage_class != csc_none)
    {
      warning (0, "useless storage class specifier in empty declaration");
      warned = 2;
    }

  if (!warned && !in_system_header && declspecs->thread_p)
    {
      warning (0, "useless %<__thread%> in empty declaration");
      warned = 2;
    }

  if (!warned && !in_system_header && (declspecs->const_p
				       || declspecs->volatile_p
				       || declspecs->restrict_p))
    {
      warning (0, "useless type qualifier in empty declaration");
      warned = 2;
    }

  if (warned != 1)
    {
      if (!found_tag)
	pedwarn ("empty declaration");
    }
}