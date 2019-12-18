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
typedef  scalar_t__ formals_style ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_ARG_TYPES (scalar_t__) ; 
 int /*<<< orphan*/  affix_data_type (char const*) ; 
 scalar_t__ ansi ; 
 char const* concat (char const*,char const*,char*,...) ; 
 int /*<<< orphan*/  data_type ; 
 char* gen_type (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ void_type_node ; 

__attribute__((used)) static const char *
gen_formal_list_for_type (tree fntype, formals_style style)
{
  const char *formal_list = "";
  tree formal_type;

  if (style != ansi)
    return "()";

  formal_type = TYPE_ARG_TYPES (fntype);
  while (formal_type && TREE_VALUE (formal_type) != void_type_node)
    {
      const char *this_type;

      if (*formal_list)
	formal_list = concat (formal_list, ", ", NULL);

      this_type = gen_type ("", TREE_VALUE (formal_type), ansi);
      formal_list
	= ((strlen (this_type))
	   ? concat (formal_list, affix_data_type (this_type), NULL)
	   : concat (formal_list, data_type, NULL));

      formal_type = TREE_CHAIN (formal_type);
    }

  /* If we got to here, then we are trying to generate an ANSI style formal
     parameters list.

     New style prototyped ANSI formal parameter lists should in theory always
     contain some stuff between the opening and closing parens, even if it is
     only "void".

     The brutal truth though is that there is lots of old K&R code out there
     which contains declarations of "pointer-to-function" parameters and
     these almost never have fully specified formal parameter lists associated
     with them.  That is, the pointer-to-function parameters are declared
     with just empty parameter lists.

     In cases such as these, protoize should really insert *something* into
     the vacant parameter lists, but what?  It has no basis on which to insert
     anything in particular.

     Here, we make life easy for protoize by trying to distinguish between
     K&R empty parameter lists and new-style prototyped parameter lists
     that actually contain "void".  In the latter case we (obviously) want
     to output the "void" verbatim, and that what we do.  In the former case,
     we do our best to give protoize something nice to insert.

     This "something nice" should be something that is still valid (when
     re-compiled) but something that can clearly indicate to the user that
     more typing information (for the parameter list) should be added (by
     hand) at some convenient moment.

     The string chosen here is a comment with question marks in it.  */

  if (!*formal_list)
    {
      if (TYPE_ARG_TYPES (fntype))
	/* assert (TREE_VALUE (TYPE_ARG_TYPES (fntype)) == void_type_node);  */
	formal_list = "void";
      else
	formal_list = "/* ??? */";
    }
  else
    {
      /* If there were at least some parameters, and if the formals-types-list
	 petered out to a NULL (i.e. without being terminated by a
	 void_type_node) then we need to tack on an ellipsis.  */
      if (!formal_type)
	formal_list = concat (formal_list, ", ...", NULL);
    }

  return concat (" (", formal_list, ")", NULL);
}