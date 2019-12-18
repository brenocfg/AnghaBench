#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {scalar_t__ (* promote_prototypes ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;

/* Variables and functions */
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_for_assignment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  default_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ic_argpass_nonproto ; 
 int /*<<< orphan*/  integer_type_node ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

tree
c_convert_parm_for_inlining (tree parm, tree value, tree fn, int argnum)
{
  tree ret, type;

  /* If FN was prototyped at the call site, the value has been converted
     already in convert_arguments.
     However, we might see a prototype now that was not in place when
     the function call was seen, so check that the VALUE actually matches
     PARM before taking an early exit.  */
  if (!value
      || (TYPE_ARG_TYPES (TREE_TYPE (fn))
	  && (TYPE_MAIN_VARIANT (TREE_TYPE (parm))
	      == TYPE_MAIN_VARIANT (TREE_TYPE (value)))))
    return value;

  type = TREE_TYPE (parm);
  ret = convert_for_assignment (type, value,
				ic_argpass_nonproto, fn,
				fn, argnum);
  if (targetm.calls.promote_prototypes (TREE_TYPE (fn))
      && INTEGRAL_TYPE_P (type)
      && (TYPE_PRECISION (type) < TYPE_PRECISION (integer_type_node)))
    ret = default_conversion (ret);
  return ret;
}