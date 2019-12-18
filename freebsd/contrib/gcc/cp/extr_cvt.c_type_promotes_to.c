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
 scalar_t__ ENUMERAL_TYPE ; 
 int MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 scalar_t__ TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ boolean_type_node ; 
 scalar_t__ c_common_type_for_size (int,int) ; 
 scalar_t__ c_promoting_integer_type_p (scalar_t__) ; 
 scalar_t__ double_type_node ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ float_type_node ; 
 int /*<<< orphan*/  int_fits_type_p (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ integer_type_node ; 
 scalar_t__ unsigned_type_node ; 
 scalar_t__ wchar_type_node ; 

tree
type_promotes_to (tree type)
{
  if (type == error_mark_node)
    return error_mark_node;

  type = TYPE_MAIN_VARIANT (type);

  /* bool always promotes to int (not unsigned), even if it's the same
     size.  */
  if (type == boolean_type_node)
    type = integer_type_node;

  /* Normally convert enums to int, but convert wide enums to something
     wider.  */
  else if (TREE_CODE (type) == ENUMERAL_TYPE
	   || type == wchar_type_node)
    {
      int precision = MAX (TYPE_PRECISION (type),
			   TYPE_PRECISION (integer_type_node));
      tree totype = c_common_type_for_size (precision, 0);
      if (TYPE_UNSIGNED (type)
	  && ! int_fits_type_p (TYPE_MAX_VALUE (type), totype))
	type = c_common_type_for_size (precision, 1);
      else
	type = totype;
    }
  else if (c_promoting_integer_type_p (type))
    {
      /* Retain unsignedness if really not getting bigger.  */
      if (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_node))
	type = unsigned_type_node;
      else
	type = integer_type_node;
    }
  else if (type == float_type_node)
    type = double_type_node;

  return type;
}