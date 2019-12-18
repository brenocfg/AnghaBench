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
struct cgraph_node {int /*<<< orphan*/  decl; struct cgraph_node* next; } ;

/* Variables and functions */
 void* BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 void* all_module_statics ; 
 int /*<<< orphan*/  bitmap_obstack_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  build_string (int,char*) ; 
 struct cgraph_node* cgraph_nodes ; 
 int /*<<< orphan*/  has_proper_scope_for_analysis (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipa_obstack ; 
 int /*<<< orphan*/  memory_identifier_string ; 
 void* module_statics_escape ; 
 void* module_statics_written ; 
 int /*<<< orphan*/  pointer_set_create () ; 
 int /*<<< orphan*/  reference_vars_to_consider ; 
 int /*<<< orphan*/  splay_tree_compare_ints ; 
 int /*<<< orphan*/  splay_tree_new_ggc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visited_nodes ; 

__attribute__((used)) static void 
ipa_init (void) 
{
  struct cgraph_node *node;
  memory_identifier_string = build_string(7, "memory");

  reference_vars_to_consider =
    splay_tree_new_ggc (splay_tree_compare_ints);

  bitmap_obstack_initialize (&ipa_obstack);
  module_statics_escape = BITMAP_ALLOC (&ipa_obstack);
  module_statics_written = BITMAP_ALLOC (&ipa_obstack);
  all_module_statics = BITMAP_ALLOC (&ipa_obstack);

  /* This will add NODE->DECL to the splay trees.  */
  for (node = cgraph_nodes; node; node = node->next)
    has_proper_scope_for_analysis (node->decl);

  /* There are some shared nodes, in particular the initializers on
     static declarations.  We do not need to scan them more than once
     since all we would be interested in are the addressof
     operations.  */
  visited_nodes = pointer_set_create ();
}