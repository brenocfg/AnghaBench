#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ipa_dfs_info {struct cgraph_node* aux; } ;
struct TYPE_5__ {scalar_t__ inlined_to; } ;
struct cgraph_node {TYPE_1__ global; struct cgraph_edge* callees; struct ipa_dfs_info* aux; } ;
struct cgraph_edge {struct cgraph_node* callee; struct cgraph_edge* next_callee; } ;
typedef  TYPE_2__* ipa_reference_vars_info_t ;
typedef  TYPE_3__* ipa_reference_local_vars_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  calls_write_all; int /*<<< orphan*/  calls_read_all; int /*<<< orphan*/  statics_written; int /*<<< orphan*/  statics_read; } ;
struct TYPE_6__ {TYPE_3__* local; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_ior_into (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cgraph_node* cgraph_master_clone (struct cgraph_node*) ; 
 int /*<<< orphan*/  dump_cgraph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_cgraph_node (int /*<<< orphan*/ ,struct cgraph_node*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_2__* get_reference_vars_info_from_cgraph (struct cgraph_node*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void 
merge_callee_local_info (struct cgraph_node *target, 
			 struct cgraph_node *x)
{
  struct cgraph_edge *e;
  ipa_reference_local_vars_info_t x_l = 
    get_reference_vars_info_from_cgraph (target)->local;

  /* Make the world safe for tail recursion.  */
  struct ipa_dfs_info *node_info = x->aux;
  
  if (node_info->aux) 
    return;

  node_info->aux = x;

  for (e = x->callees; e; e = e->next_callee) 
    {
      struct cgraph_node *y = e->callee;
      if (y->global.inlined_to) 
	{
	  ipa_reference_vars_info_t y_info;
	  ipa_reference_local_vars_info_t y_l;
	  struct cgraph_node* orig_y = y;
	 
	  y = cgraph_master_clone (y);
	  if (y)
	    {
	      y_info = get_reference_vars_info_from_cgraph (y);
	      y_l = y_info->local;
	      if (x_l != y_l)
		{
		  bitmap_ior_into (x_l->statics_read,
				   y_l->statics_read);
		  bitmap_ior_into (x_l->statics_written,
				   y_l->statics_written);
		}
	      x_l->calls_read_all |= y_l->calls_read_all;
	      x_l->calls_write_all |= y_l->calls_write_all;
	      merge_callee_local_info (target, y);
	    }
	  else 
	    {
	      fprintf(stderr, "suspect inlining of ");
	      dump_cgraph_node (stderr, orig_y);
	      fprintf(stderr, "\ninto ");
	      dump_cgraph_node (stderr, target);
	      dump_cgraph (stderr);
	      gcc_assert(false);
	    }
	}
    }

  node_info->aux = NULL;
}