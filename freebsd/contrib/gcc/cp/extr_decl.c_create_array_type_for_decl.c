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

/* Variables and functions */
 int ARRAY_TYPE ; 
#define  FUNCTION_TYPE 131 
#define  METHOD_TYPE 130 
 scalar_t__ NULL_TREE ; 
#define  REFERENCE_TYPE 129 
 int TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_DOMAIN (scalar_t__) ; 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  abstract_virtuals_error (scalar_t__,scalar_t__) ; 
 scalar_t__ build_cplus_array_type (scalar_t__,scalar_t__) ; 
 scalar_t__ compute_array_index_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ error_mark_node ; 

__attribute__((used)) static tree
create_array_type_for_decl (tree name, tree type, tree size)
{
  tree itype = NULL_TREE;
  const char* error_msg;

  /* If things have already gone awry, bail now.  */
  if (type == error_mark_node || size == error_mark_node)
    return error_mark_node;

  /* Assume that everything will go OK.  */
  error_msg = NULL;

  /* There are some types which cannot be array elements.  */
  switch (TREE_CODE (type))
    {
    case VOID_TYPE:
      error_msg = "array of void";
      break;

    case FUNCTION_TYPE:
      error_msg = "array of functions";
      break;

    case REFERENCE_TYPE:
      error_msg = "array of references";
      break;

    case METHOD_TYPE:
      error_msg = "array of function members";
      break;

    default:
      break;
    }

  /* If something went wrong, issue an error-message and return.  */
  if (error_msg)
    {
      if (name)
	error ("declaration of %qD as %s", name, error_msg);
      else
	error ("creating %s", error_msg);

      return error_mark_node;
    }

  /* [dcl.array]

     The constant expressions that specify the bounds of the arrays
     can be omitted only for the first member of the sequence.  */
  if (TREE_CODE (type) == ARRAY_TYPE && !TYPE_DOMAIN (type))
    {
      if (name)
	error ("declaration of %qD as multidimensional array must "
	       "have bounds for all dimensions except the first",
	       name);
      else
	error ("multidimensional array must have bounds for all "
	       "dimensions except the first");

      return error_mark_node;
    }

  /* Figure out the index type for the array.  */
  if (size)
    itype = compute_array_index_type (name, size);

  /* [dcl.array]
     T is called the array element type; this type shall not be [...] an
     abstract class type.  */
  abstract_virtuals_error (name, type);

  return build_cplus_array_type (type, itype);
}