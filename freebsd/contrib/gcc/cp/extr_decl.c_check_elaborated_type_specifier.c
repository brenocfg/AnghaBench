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
typedef  char* tree ;
typedef  enum tag_types { ____Placeholder_tag_types } tag_types ;

/* Variables and functions */
 scalar_t__ CLASSTYPE_IS_TEMPLATE (char*) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_TEMPLATE (char*) ; 
 int /*<<< orphan*/  DECL_IMPLICIT_TYPEDEF_P (char*) ; 
 char* DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_SELF_REFERENCE_P (char*) ; 
 scalar_t__ ENUMERAL_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TEMPLATE_TYPE_PARM ; 
 scalar_t__ TREE_CODE (char*) ; 
 char* TREE_TYPE (char*) ; 
 char* TYPE_NAME (char*) ; 
 scalar_t__ UNION_TYPE ; 
 int enum_type ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 char* error_mark_node ; 
 char* tag_name (int) ; 
 int typename_type ; 

tree
check_elaborated_type_specifier (enum tag_types tag_code,
				 tree decl,
				 bool allow_template_p)
{
  tree type;

  /* In the case of:

       struct S { struct S *p; };

     name lookup will find the TYPE_DECL for the implicit "S::S"
     typedef.  Adjust for that here.  */
  if (DECL_SELF_REFERENCE_P (decl))
    decl = TYPE_NAME (TREE_TYPE (decl));

  type = TREE_TYPE (decl);

  /* Check TEMPLATE_TYPE_PARM first because DECL_IMPLICIT_TYPEDEF_P
     is false for this case as well.  */
  if (TREE_CODE (type) == TEMPLATE_TYPE_PARM)
    {
      error ("using template type parameter %qT after %qs",
	     type, tag_name (tag_code));
      return error_mark_node;
    }
  /*   [dcl.type.elab]

       If the identifier resolves to a typedef-name or a template
       type-parameter, the elaborated-type-specifier is ill-formed.

     In other words, the only legitimate declaration to use in the
     elaborated type specifier is the implicit typedef created when
     the type is declared.  */
  else if (!DECL_IMPLICIT_TYPEDEF_P (decl)
	   && tag_code != typename_type)
    {
      error ("using typedef-name %qD after %qs", decl, tag_name (tag_code));
      error ("%q+D has a previous declaration here", decl);
      return error_mark_node;
    }
  else if (TREE_CODE (type) != RECORD_TYPE
	   && TREE_CODE (type) != UNION_TYPE
	   && tag_code != enum_type
	   && tag_code != typename_type)
    {
      error ("%qT referred to as %qs", type, tag_name (tag_code));
      error ("%q+T has a previous declaration here", type);
      return error_mark_node;
    }
  else if (TREE_CODE (type) != ENUMERAL_TYPE
	   && tag_code == enum_type)
    {
      error ("%qT referred to as enum", type);
      error ("%q+T has a previous declaration here", type);
      return error_mark_node;
    }
  else if (!allow_template_p
	   && TREE_CODE (type) == RECORD_TYPE
	   && CLASSTYPE_IS_TEMPLATE (type))
    {
      /* If a class template appears as elaborated type specifier
	 without a template header such as:

	   template <class T> class C {};
	   void f(class C);		// No template header here

	 then the required template argument is missing.  */
      error ("template argument required for %<%s %T%>",
	     tag_name (tag_code),
	     DECL_NAME (CLASSTYPE_TI_TEMPLATE (type)));
      return error_mark_node;
    }

  return type;
}