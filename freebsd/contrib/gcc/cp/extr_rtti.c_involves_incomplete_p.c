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
 int /*<<< orphan*/  COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
#define  OFFSET_TYPE 131 
#define  POINTER_TYPE 130 
#define  RECORD_TYPE 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 128 
 int target_incomplete_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
involves_incomplete_p (tree type)
{
  switch (TREE_CODE (type))
    {
    case POINTER_TYPE:
      return target_incomplete_p (TREE_TYPE (type));

    case OFFSET_TYPE:
    ptrmem:
      return
	(target_incomplete_p (TYPE_PTRMEM_POINTED_TO_TYPE (type))
	 || !COMPLETE_TYPE_P (TYPE_PTRMEM_CLASS_TYPE (type)));

    case RECORD_TYPE:
      if (TYPE_PTRMEMFUNC_P (type))
	goto ptrmem;
      /* Fall through.  */
    case UNION_TYPE:
      if (!COMPLETE_TYPE_P (type))
	return true;

    default:
      /* All other types do not involve incomplete class types.  */
      return false;
    }
}