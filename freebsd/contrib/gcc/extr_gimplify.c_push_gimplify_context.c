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
struct gimplify_ctx {int /*<<< orphan*/  temp_htab; struct gimplify_ctx* prev_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  gimple_tree_eq ; 
 int /*<<< orphan*/  gimple_tree_hash ; 
 struct gimplify_ctx* gimplify_ctxp ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize ; 
 scalar_t__ xcalloc (int,int) ; 

void
push_gimplify_context (void)
{
  struct gimplify_ctx *c;

  c = (struct gimplify_ctx *) xcalloc (1, sizeof (struct gimplify_ctx));
  c->prev_context = gimplify_ctxp;
  if (optimize)
    c->temp_htab = htab_create (1000, gimple_tree_hash, gimple_tree_eq, free);

  gimplify_ctxp = c;
}