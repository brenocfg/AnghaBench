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

/* Variables and functions */
 int /*<<< orphan*/  INTEGRAL_TYPE_P (char*) ; 
 scalar_t__ POINTER_TYPE ; 
 int /*<<< orphan*/  POINTER_TYPE_P (char*) ; 
 scalar_t__ TREE_CODE (char*) ; 
 char* TREE_TYPE (char*) ; 
 char* TREE_VALUE (char*) ; 
 int /*<<< orphan*/  TYPE_SIZE_UNIT (char*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int tree_low_cst (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sync_resolve_size (tree function, tree params)
{
  tree type;
  int size;

  if (params == NULL)
    {
      error ("too few arguments to function %qE", function);
      return 0;
    }

  type = TREE_TYPE (TREE_VALUE (params));
  if (TREE_CODE (type) != POINTER_TYPE)
    goto incompatible;

  type = TREE_TYPE (type);
  if (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
    goto incompatible;

  size = tree_low_cst (TYPE_SIZE_UNIT (type), 1);
  if (size == 1 || size == 2 || size == 4 || size == 8 || size == 16)
    return size;

 incompatible:
  error ("incompatible type for argument %d of %qE", 1, function);
  return 0;
}