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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  scalar_t__ tree ;
struct sra_elt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_new_referenced_vars (int /*<<< orphan*/ ) ; 
 int generate_element_init_1 (struct sra_elt*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  pop_gimplify_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_gimplify_context () ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (scalar_t__) ; 
 int /*<<< orphan*/  tsi_stmt_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
generate_element_init (struct sra_elt *elt, tree init, tree *list_p)
{
  bool ret;

  push_gimplify_context ();
  ret = generate_element_init_1 (elt, init, list_p);
  pop_gimplify_context (NULL);

  /* The replacement can expose previously unreferenced variables.  */
  if (ret && *list_p)
    {
      tree_stmt_iterator i;

      for (i = tsi_start (*list_p); !tsi_end_p (i); tsi_next (&i))
	find_new_referenced_vars (tsi_stmt_ptr (i));
    }

  return ret;
}