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
struct et_node {int /*<<< orphan*/ * parent_occ; int /*<<< orphan*/  rightmost_occ; int /*<<< orphan*/ * son; int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; int /*<<< orphan*/ * father; void* data; } ;

/* Variables and functions */
 scalar_t__ create_alloc_pool (char*,int,int) ; 
 int /*<<< orphan*/  et_new_occ (struct et_node*) ; 
 scalar_t__ et_nodes ; 
 struct et_node* pool_alloc (scalar_t__) ; 

struct et_node *
et_new_tree (void *data)
{
  struct et_node *nw;
  
  if (!et_nodes)
    et_nodes = create_alloc_pool ("et_node pool", sizeof (struct et_node), 300);
  nw = pool_alloc (et_nodes);

  nw->data = data;
  nw->father = NULL;
  nw->left = NULL;
  nw->right = NULL;
  nw->son = NULL;

  nw->rightmost_occ = et_new_occ (nw);
  nw->parent_occ = NULL;

  return nw;
}