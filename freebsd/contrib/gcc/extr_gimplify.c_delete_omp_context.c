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
struct gimplify_omp_ctx {int /*<<< orphan*/  privatized_types; int /*<<< orphan*/  variables; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDELETE (struct gimplify_omp_ctx*) ; 
 int /*<<< orphan*/  pointer_set_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splay_tree_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
delete_omp_context (struct gimplify_omp_ctx *c)
{
  splay_tree_delete (c->variables);
  pointer_set_destroy (c->privatized_types);
  XDELETE (c);
}