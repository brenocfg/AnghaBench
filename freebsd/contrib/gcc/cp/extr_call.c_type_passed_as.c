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
 scalar_t__ COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ INT_CST_LT_UNSIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_ADDRESSABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_QUAL_RESTRICT ; 
 int /*<<< orphan*/  TYPE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_qualified_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_reference_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_type_node ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

tree
type_passed_as (tree type)
{
  /* Pass classes with copy ctors by invisible reference.  */
  if (TREE_ADDRESSABLE (type))
    {
      type = build_reference_type (type);
      /* There are no other pointers to this temporary.  */
      type = build_qualified_type (type, TYPE_QUAL_RESTRICT);
    }
  else if (targetm.calls.promote_prototypes (type)
	   && INTEGRAL_TYPE_P (type)
	   && COMPLETE_TYPE_P (type)
	   && INT_CST_LT_UNSIGNED (TYPE_SIZE (type),
				   TYPE_SIZE (integer_type_node)))
    type = integer_type_node;

  return type;
}