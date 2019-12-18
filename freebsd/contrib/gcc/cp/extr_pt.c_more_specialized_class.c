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
 int /*<<< orphan*/  CLASSTYPE_TI_ARGS (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 scalar_t__ get_class_bindings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processing_template_decl ; 

__attribute__((used)) static int
more_specialized_class (tree pat1, tree pat2)
{
  tree targs;
  tree tmpl1, tmpl2;
  int winner = 0;

  tmpl1 = TREE_TYPE (pat1);
  tmpl2 = TREE_TYPE (pat2);

  /* Just like what happens for functions, if we are ordering between
     different class template specializations, we may encounter dependent
     types in the arguments, and we need our dependency check functions
     to behave correctly.  */
  ++processing_template_decl;
  targs = get_class_bindings (TREE_VALUE (pat1),
			      CLASSTYPE_TI_ARGS (tmpl1),
			      CLASSTYPE_TI_ARGS (tmpl2));
  if (targs)
    --winner;

  targs = get_class_bindings (TREE_VALUE (pat2),
			      CLASSTYPE_TI_ARGS (tmpl2),
			      CLASSTYPE_TI_ARGS (tmpl1));
  if (targs)
    ++winner;
  --processing_template_decl;

  return winner;
}