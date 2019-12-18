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
typedef  int tsubst_flags_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMPLATE_TYPE_PARM ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPENAME_TYPE ; 
 scalar_t__ TYPE_PTR_TO_MEMBER_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int tf_error ; 

__attribute__((used)) static int
invalid_nontype_parm_type_p (tree type, tsubst_flags_t complain)
{
  if (INTEGRAL_TYPE_P (type))
    return 0;
  else if (POINTER_TYPE_P (type))
    return 0;
  else if (TYPE_PTR_TO_MEMBER_P (type))
    return 0;
  else if (TREE_CODE (type) == TEMPLATE_TYPE_PARM)
    return 0;
  else if (TREE_CODE (type) == TYPENAME_TYPE)
    return 0;

  if (complain & tf_error)
    error ("%q#T is not a valid type for a template constant parameter", type);
  return 1;
}