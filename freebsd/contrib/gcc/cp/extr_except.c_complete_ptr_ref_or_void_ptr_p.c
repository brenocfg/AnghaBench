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
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_type_or_else (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
complete_ptr_ref_or_void_ptr_p (tree type, tree from)
{
  int is_ptr;

  /* Check complete.  */
  type = complete_type_or_else (type, from);
  if (!type)
    return 0;

  /* Or a pointer or ref to one, or cv void *.  */
  is_ptr = TREE_CODE (type) == POINTER_TYPE;
  if (is_ptr || TREE_CODE (type) == REFERENCE_TYPE)
    {
      tree core = TREE_TYPE (type);

      if (is_ptr && VOID_TYPE_P (core))
	/* OK */;
      else if (!complete_type_or_else (core, from))
	return 0;
    }
  return 1;
}