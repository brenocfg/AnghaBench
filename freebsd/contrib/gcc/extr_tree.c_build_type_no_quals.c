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
typedef  void* tree ;

/* Variables and functions */
#define  POINTER_TYPE 129 
#define  REFERENCE_TYPE 128 
 int TREE_CODE (void*) ; 
 void* TREE_TYPE (void*) ; 
 void* TYPE_MAIN_VARIANT (void*) ; 
 int /*<<< orphan*/  TYPE_MODE (void*) ; 
 int /*<<< orphan*/  TYPE_REF_CAN_ALIAS_ALL (void*) ; 
 void* build_pointer_type_for_mode (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* build_reference_type_for_mode (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
build_type_no_quals (tree t)
{
  switch (TREE_CODE (t))
    {
    case POINTER_TYPE:
      return build_pointer_type_for_mode (build_type_no_quals (TREE_TYPE (t)),
					  TYPE_MODE (t),
					  TYPE_REF_CAN_ALIAS_ALL (t));
    case REFERENCE_TYPE:
      return
	build_reference_type_for_mode (build_type_no_quals (TREE_TYPE (t)),
				       TYPE_MODE (t),
				       TYPE_REF_CAN_ALIAS_ALL (t));
    default:
      return TYPE_MAIN_VARIANT (t);
    }
}