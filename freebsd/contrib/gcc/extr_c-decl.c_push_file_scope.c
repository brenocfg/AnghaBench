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
 int /*<<< orphan*/  DECL_NAME (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  bind (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ current_scope ; 
 scalar_t__ file_scope ; 
 int /*<<< orphan*/  push_scope () ; 
 int /*<<< orphan*/  start_fname_decls () ; 
 scalar_t__ visible_builtins ; 

void
push_file_scope (void)
{
  tree decl;

  if (file_scope)
    return;

  push_scope ();
  file_scope = current_scope;

  start_fname_decls ();

  for (decl = visible_builtins; decl; decl = TREE_CHAIN (decl))
    bind (DECL_NAME (decl), decl, file_scope,
	  /*invisible=*/false, /*nested=*/true);
}