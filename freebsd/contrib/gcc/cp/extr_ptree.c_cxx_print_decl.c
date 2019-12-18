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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_CONTAINS_STRUCT (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_LANG_SPECIFIC (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_MUTABLE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_PENDING_INLINE_INFO (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_SORTED_FIELDS (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_TEMPLATE_INFO (int /*<<< orphan*/ ) ; 
 scalar_t__ FIELD_DECL ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TS_DECL_COMMON ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  indent_to (int /*<<< orphan*/ *,int) ; 

void
cxx_print_decl (FILE *file, tree node, int indent)
{
  if (TREE_CODE (node) == FIELD_DECL)
    {
      if (DECL_MUTABLE_P (node))
	{
	  indent_to (file, indent + 3);
	  fprintf (file, " mutable ");
	}
      return;
    }

  if (!CODE_CONTAINS_STRUCT (TREE_CODE (node), TS_DECL_COMMON)
      || !DECL_LANG_SPECIFIC (node))
    return;
  indent_to (file, indent + 3);
  if (TREE_CODE (node) == FUNCTION_DECL
      && DECL_PENDING_INLINE_INFO (node))
    fprintf (file, " pending-inline-info %p",
	     (void *) DECL_PENDING_INLINE_INFO (node));
  if (TREE_CODE (node) == TYPE_DECL
      && DECL_SORTED_FIELDS (node))
    fprintf (file, " sorted-fields %p",
	     (void *) DECL_SORTED_FIELDS (node));
  if ((TREE_CODE (node) == FUNCTION_DECL || TREE_CODE (node) == VAR_DECL)
      && DECL_TEMPLATE_INFO (node))
    fprintf (file, " template-info %p",
	     (void *) DECL_TEMPLATE_INFO (node));
}