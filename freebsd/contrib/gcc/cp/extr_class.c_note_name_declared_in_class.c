#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char* tree ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  int /*<<< orphan*/  splay_tree ;
struct TYPE_5__ {int /*<<< orphan*/  names_used; } ;
struct TYPE_4__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVL_CURRENT (char*) ; 
 int current_class_depth ; 
 TYPE_3__* current_class_stack ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
note_name_declared_in_class (tree name, tree decl)
{
  splay_tree names_used;
  splay_tree_node n;

  /* Look to see if we ever used this name.  */
  names_used
    = current_class_stack[current_class_depth - 1].names_used;
  if (!names_used)
    return;

  n = splay_tree_lookup (names_used, (splay_tree_key) name);
  if (n)
    {
      /* [basic.scope.class]

	 A name N used in a class S shall refer to the same declaration
	 in its context and when re-evaluated in the completed scope of
	 S.  */
      error ("declaration of %q#D", decl);
      error ("changes meaning of %qD from %q+#D",
	     DECL_NAME (OVL_CURRENT (decl)), (tree) n->value);
    }
}