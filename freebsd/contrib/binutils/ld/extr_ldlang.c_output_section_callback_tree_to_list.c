#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ lang_wild_statement_type ;
struct TYPE_7__ {struct TYPE_7__* right; int /*<<< orphan*/  section; struct TYPE_7__* left; } ;
typedef  TYPE_2__ lang_section_bst_type ;
typedef  int /*<<< orphan*/  lang_output_section_statement_type ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  lang_add_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
output_section_callback_tree_to_list (lang_wild_statement_type *ptr,
				      lang_section_bst_type *tree,
				      void *output)
{
  if (tree->left)
    output_section_callback_tree_to_list (ptr, tree->left, output);

  lang_add_section (&ptr->children, tree->section,
		    (lang_output_section_statement_type *) output);

  if (tree->right)
    output_section_callback_tree_to_list (ptr, tree->right, output);

  free (tree);
}