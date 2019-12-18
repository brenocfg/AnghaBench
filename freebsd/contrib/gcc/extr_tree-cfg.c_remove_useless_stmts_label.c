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
struct rus_data {int has_label; int repeat; int /*<<< orphan*/ * last_goto; } ;

/* Variables and functions */
 scalar_t__ DECL_NONLOCAL (scalar_t__) ; 
 scalar_t__ GOTO_DESTINATION (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_EXPR_LABEL (scalar_t__) ; 
 int /*<<< orphan*/  build_empty_stmt () ; 

__attribute__((used)) static void
remove_useless_stmts_label (tree *stmt_p, struct rus_data *data)
{
  tree label = LABEL_EXPR_LABEL (*stmt_p);

  data->has_label = true;

  /* We do want to jump across non-local label receiver code.  */
  if (DECL_NONLOCAL (label))
    data->last_goto = NULL;

  else if (data->last_goto && GOTO_DESTINATION (*data->last_goto) == label)
    {
      *data->last_goto = build_empty_stmt ();
      data->repeat = true;
    }

  /* ??? Add something here to delete unused labels.  */
}