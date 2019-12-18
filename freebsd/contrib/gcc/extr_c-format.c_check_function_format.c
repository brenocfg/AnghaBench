#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_5__ {scalar_t__ first_arg_num; size_t format_type; } ;
typedef  TYPE_1__ function_format_info ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 scalar_t__ FMT_FLAG_ARG_CONVERT ; 
 int /*<<< orphan*/  IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wmissing_format_attribute ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_PURPOSE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ATTRIBUTES (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ char_type_node ; 
 int /*<<< orphan*/  check_format_info (TYPE_1__*,scalar_t__) ; 
 scalar_t__ current_function_decl ; 
 int /*<<< orphan*/  decode_format_attr (scalar_t__,TYPE_1__*,int) ; 
 scalar_t__ decode_format_type (int /*<<< orphan*/ ) ; 
 TYPE_2__* format_types ; 
 scalar_t__ is_attribute_p (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ warn_format ; 
 scalar_t__ warn_missing_format_attribute ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
check_function_format (tree attrs, tree params)
{
  tree a;

  /* See if this function has any format attributes.  */
  for (a = attrs; a; a = TREE_CHAIN (a))
    {
      if (is_attribute_p ("format", TREE_PURPOSE (a)))
	{
	  /* Yup; check it.  */
	  function_format_info info;
	  decode_format_attr (TREE_VALUE (a), &info, 1);
	  if (warn_format)
	    check_format_info (&info, params);
	  if (warn_missing_format_attribute && info.first_arg_num == 0
	      && (format_types[info.format_type].flags
		  & (int) FMT_FLAG_ARG_CONVERT))
	    {
	      tree c;
	      for (c = TYPE_ATTRIBUTES (TREE_TYPE (current_function_decl));
		   c;
		   c = TREE_CHAIN (c))
		if (is_attribute_p ("format", TREE_PURPOSE (c))
		    && (decode_format_type (IDENTIFIER_POINTER
					    (TREE_VALUE (TREE_VALUE (c))))
			== info.format_type))
		  break;
	      if (c == NULL_TREE)
		{
		  /* Check if the current function has a parameter to which
		     the format attribute could be attached; if not, it
		     can't be a candidate for a format attribute, despite
		     the vprintf-like or vscanf-like call.  */
		  tree args;
		  for (args = DECL_ARGUMENTS (current_function_decl);
		       args != 0;
		       args = TREE_CHAIN (args))
		    {
		      if (TREE_CODE (TREE_TYPE (args)) == POINTER_TYPE
			  && (TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (args)))
			      == char_type_node))
			break;
		    }
		  if (args != 0)
		    warning (OPT_Wmissing_format_attribute, "function might "
			     "be possible candidate for %qs format attribute",
			     format_types[info.format_type].name);
		}
	    }
	}
    }
}