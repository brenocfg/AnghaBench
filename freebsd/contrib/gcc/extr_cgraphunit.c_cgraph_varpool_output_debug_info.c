#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cgraph_varpool_node {struct cgraph_varpool_node* next_needed; int /*<<< orphan*/  decl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* global_decl ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ BLOCK ; 
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TV_SYMOUT ; 
 struct cgraph_varpool_node* cgraph_varpool_assembled_nodes_queue ; 
 TYPE_1__* debug_hooks ; 
 scalar_t__ errorcount ; 
 scalar_t__ sorrycount ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cgraph_varpool_output_debug_info (void)
{
  timevar_push (TV_SYMOUT);
  if (errorcount == 0 && sorrycount == 0)
    while (cgraph_varpool_assembled_nodes_queue)
      {
	struct cgraph_varpool_node *node = cgraph_varpool_assembled_nodes_queue;

	/* Local static variables are never seen by check_global_declarations
	   so we need to output debug info by hand.  */
	if (DECL_CONTEXT (node->decl)
	    && (TREE_CODE (DECL_CONTEXT (node->decl)) == BLOCK
		|| TREE_CODE (DECL_CONTEXT (node->decl)) == FUNCTION_DECL)
	    && errorcount == 0 && sorrycount == 0)
	     (*debug_hooks->global_decl) (node->decl);
	cgraph_varpool_assembled_nodes_queue = node->next_needed;
	node->next_needed = 0;
      }
  timevar_pop (TV_SYMOUT);
}