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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ METHOD_TYPE ; 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TEMPLATE_TYPE_PARM ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int TYPE_QUAL_CONST ; 
 int TYPE_QUAL_RESTRICT ; 
 int TYPE_QUAL_VOLATILE ; 
 int UNIFY_ALLOW_LESS_CV_QUAL ; 
 int UNIFY_ALLOW_MORE_CV_QUAL ; 
 int UNIFY_ALLOW_OUTER_LESS_CV_QUAL ; 
 int UNIFY_ALLOW_OUTER_MORE_CV_QUAL ; 
 int cp_type_quals (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_cv_quals_for_unify (int strict, tree arg, tree parm)
{
  int arg_quals = cp_type_quals (arg);
  int parm_quals = cp_type_quals (parm);

  if (TREE_CODE (parm) == TEMPLATE_TYPE_PARM
      && !(strict & UNIFY_ALLOW_OUTER_MORE_CV_QUAL))
    {
      /*  Although a CVR qualifier is ignored when being applied to a
	  substituted template parameter ([8.3.2]/1 for example), that
	  does not apply during deduction [14.8.2.4]/1, (even though
	  that is not explicitly mentioned, [14.8.2.4]/9 indicates
	  this).  Except when we're allowing additional CV qualifiers
	  at the outer level [14.8.2.1]/3,1st bullet.  */
      if ((TREE_CODE (arg) == REFERENCE_TYPE
	   || TREE_CODE (arg) == FUNCTION_TYPE
	   || TREE_CODE (arg) == METHOD_TYPE)
	  && (parm_quals & (TYPE_QUAL_CONST | TYPE_QUAL_VOLATILE)))
	return 0;

      if ((!POINTER_TYPE_P (arg) && TREE_CODE (arg) != TEMPLATE_TYPE_PARM)
	  && (parm_quals & TYPE_QUAL_RESTRICT))
	return 0;
    }

  if (!(strict & (UNIFY_ALLOW_MORE_CV_QUAL | UNIFY_ALLOW_OUTER_MORE_CV_QUAL))
      && (arg_quals & parm_quals) != parm_quals)
    return 0;

  if (!(strict & (UNIFY_ALLOW_LESS_CV_QUAL | UNIFY_ALLOW_OUTER_LESS_CV_QUAL))
      && (parm_quals & arg_quals) != arg_quals)
    return 0;

  return 1;
}