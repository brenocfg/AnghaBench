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
#define  BOOLEAN_TYPE 131 
#define  INTEGER_TYPE 130 
 int POINTER_TYPE ; 
#define  REAL_TYPE 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_QUAL_CONST ; 
 scalar_t__ TYPE_UNQUALIFIED ; 
#define  VOID_TYPE 128 
 scalar_t__ cp_type_quals (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
typeinfo_in_lib_p (tree type)
{
  /* The typeinfo objects for `T*' and `const T*' are in the runtime
     library for simple types T.  */
  if (TREE_CODE (type) == POINTER_TYPE
      && (cp_type_quals (TREE_TYPE (type)) == TYPE_QUAL_CONST
	  || cp_type_quals (TREE_TYPE (type)) == TYPE_UNQUALIFIED))
    type = TREE_TYPE (type);

  switch (TREE_CODE (type))
    {
    case INTEGER_TYPE:
    case BOOLEAN_TYPE:
    case REAL_TYPE:
    case VOID_TYPE:
      return true;

    default:
      return false;
    }
}