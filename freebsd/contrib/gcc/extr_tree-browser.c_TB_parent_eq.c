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
 scalar_t__ EXPRESSION_CLASS_P (scalar_t__) ; 
 int /*<<< orphan*/  TEST_CHILD (int) ; 
 int /*<<< orphan*/  TREE_CODE (scalar_t__) ; 
 int TREE_CODE_LENGTH (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
TB_parent_eq (const void *p1, const void *p2)
{
  tree node, parent;
  node = (tree) p2;
  parent = (tree) p1;

  if (p1 == NULL || p2 == NULL)
    return 0;

  if (EXPRESSION_CLASS_P (parent))
    {

#define TEST_CHILD(N) do {               \
  if (node == TREE_OPERAND (parent, N))  \
    return 1;                            \
} while (0)

    switch (TREE_CODE_LENGTH (TREE_CODE (parent)))
      {
      case 4:
	TEST_CHILD (0);
	TEST_CHILD (1);
	TEST_CHILD (2);
	TEST_CHILD (3);
	break;

      case 3:
	TEST_CHILD (0);
	TEST_CHILD (1);
	TEST_CHILD (2);
	break;

      case 2:
	TEST_CHILD (0);
	TEST_CHILD (1);
	break;

      case 1:
	TEST_CHILD (0);
	break;

      case 0:
      default:
	/* No children: nothing to do.  */
	break;
      }
#undef TEST_CHILD
    }

  return 0;
}