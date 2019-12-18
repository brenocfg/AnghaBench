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
typedef  int /*<<< orphan*/  tree ;
struct c_binding {int /*<<< orphan*/  decl; int /*<<< orphan*/  id; struct c_binding* prev; } ;
struct TYPE_2__ {struct c_binding* bindings; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_SYNTHESIZED_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
#define  ENUMERAL_TYPE 132 
#define  FUNCTION_DECL 131 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RECORD_TYPE 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STATIC (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 129 
#define  VAR_DECL 128 
 TYPE_1__* current_scope ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  flag_isoc99 ; 

tree
check_for_loop_decls (void)
{
  struct c_binding *b;
  tree one_decl = NULL_TREE;
  int n_decls = 0;


  if (!flag_isoc99)
    {
      /* If we get here, declarations have been used in a for loop without
	 the C99 for loop scope.  This doesn't make much sense, so don't
	 allow it.  */
      error ("%<for%> loop initial declaration used outside C99 mode");
      return NULL_TREE;
    }
  /* C99 subclause 6.8.5 paragraph 3:

       [#3]  The  declaration  part  of  a for statement shall only
       declare identifiers for objects having storage class auto or
       register.

     It isn't clear whether, in this sentence, "identifiers" binds to
     "shall only declare" or to "objects" - that is, whether all identifiers
     declared must be identifiers for objects, or whether the restriction
     only applies to those that are.  (A question on this in comp.std.c
     in November 2000 received no answer.)  We implement the strictest
     interpretation, to avoid creating an extension which later causes
     problems.  */

  for (b = current_scope->bindings; b; b = b->prev)
    {
      tree id = b->id;
      tree decl = b->decl;

      if (!id)
	continue;

      switch (TREE_CODE (decl))
	{
	case VAR_DECL:
	  if (TREE_STATIC (decl))
	    error ("declaration of static variable %q+D in %<for%> loop "
		   "initial declaration", decl);
	  else if (DECL_EXTERNAL (decl))
	    error ("declaration of %<extern%> variable %q+D in %<for%> loop "
		   "initial declaration", decl);
	  break;

	case RECORD_TYPE:
	  error ("%<struct %E%> declared in %<for%> loop initial declaration",
		 id);
	  break;
	case UNION_TYPE:
	  error ("%<union %E%> declared in %<for%> loop initial declaration",
		 id);
	  break;
	case ENUMERAL_TYPE:
	  error ("%<enum %E%> declared in %<for%> loop initial declaration",
		 id);
	  break;
	/* APPLE LOCAL begin radar 6268817 */
	 case FUNCTION_DECL:
	/* Block helper function can be declared in the statement block
	 for the for-loop declarations. */
	if (BLOCK_SYNTHESIZED_FUNC (decl))
		break;
	/* APPLE LOCAL end radar 6268817 */
	default:
	  error ("declaration of non-variable %q+D in %<for%> loop "
		 "initial declaration", decl);
	}

      n_decls++;
      one_decl = decl;
    }

  return n_decls == 1 ? one_decl : NULL_TREE;
}