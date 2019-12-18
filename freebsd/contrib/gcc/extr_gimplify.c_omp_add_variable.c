#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct gimplify_omp_ctx {int /*<<< orphan*/  variables; } ;
typedef  TYPE_2__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
struct TYPE_5__ {scalar_t__ (* omp_privatize_by_reference ) (scalar_t__) ;} ;
struct TYPE_7__ {TYPE_1__ decls; } ;
struct TYPE_6__ {unsigned int value; } ;

/* Variables and functions */
 int DECL_P (scalar_t__) ; 
 scalar_t__ DECL_SIZE (scalar_t__) ; 
 scalar_t__ DECL_SIZE_UNIT (scalar_t__) ; 
 scalar_t__ DECL_VALUE_EXPR (scalar_t__) ; 
 unsigned int GOVD_DATA_SHARE_CLASS ; 
 unsigned int GOVD_DEBUG_PRIVATE ; 
 unsigned int GOVD_EXPLICIT ; 
 unsigned int GOVD_FIRSTPRIVATE ; 
 unsigned int GOVD_LASTPRIVATE ; 
 unsigned int GOVD_LOCAL ; 
 unsigned int GOVD_PRIVATE ; 
 unsigned int GOVD_SEEN ; 
 unsigned int GOVD_SHARED ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ TREE_ADDRESSABLE (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_NEEDS_CONSTRUCTING (scalar_t__) ; 
 scalar_t__ TYPE_SIZE_UNIT (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_4__ lang_hooks ; 
 int /*<<< orphan*/  omp_firstprivatize_type_sizes (struct gimplify_omp_ctx*,scalar_t__) ; 
 int /*<<< orphan*/  omp_firstprivatize_variable (struct gimplify_omp_ctx*,scalar_t__) ; 
 int /*<<< orphan*/  omp_notice_variable (struct gimplify_omp_ctx*,scalar_t__,int) ; 
 int /*<<< orphan*/  splay_tree_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (scalar_t__) ; 

__attribute__((used)) static void
omp_add_variable (struct gimplify_omp_ctx *ctx, tree decl, unsigned int flags)
{
  splay_tree_node n;
  unsigned int nflags;
  tree t;

  if (decl == error_mark_node || TREE_TYPE (decl) == error_mark_node)
    return;

  /* Never elide decls whose type has TREE_ADDRESSABLE set.  This means
     there are constructors involved somewhere.  */
  if (TREE_ADDRESSABLE (TREE_TYPE (decl))
      || TYPE_NEEDS_CONSTRUCTING (TREE_TYPE (decl)))
    flags |= GOVD_SEEN;

  n = splay_tree_lookup (ctx->variables, (splay_tree_key)decl);
  if (n != NULL)
    {
      /* We shouldn't be re-adding the decl with the same data
	 sharing class.  */
      gcc_assert ((n->value & GOVD_DATA_SHARE_CLASS & flags) == 0);
      /* The only combination of data sharing classes we should see is
	 FIRSTPRIVATE and LASTPRIVATE.  */
      nflags = n->value | flags;
      gcc_assert ((nflags & GOVD_DATA_SHARE_CLASS)
		  == (GOVD_FIRSTPRIVATE | GOVD_LASTPRIVATE));
      n->value = nflags;
      return;
    }

  /* When adding a variable-sized variable, we have to handle all sorts
     of additional bits of data: the pointer replacement variable, and 
     the parameters of the type.  */
  if (DECL_SIZE (decl) && TREE_CODE (DECL_SIZE (decl)) != INTEGER_CST)
    {
      /* Add the pointer replacement variable as PRIVATE if the variable
	 replacement is private, else FIRSTPRIVATE since we'll need the
	 address of the original variable either for SHARED, or for the
	 copy into or out of the context.  */
      if (!(flags & GOVD_LOCAL))
	{
	  nflags = flags & GOVD_PRIVATE ? GOVD_PRIVATE : GOVD_FIRSTPRIVATE;
	  nflags |= flags & GOVD_SEEN;
	  t = DECL_VALUE_EXPR (decl);
	  gcc_assert (TREE_CODE (t) == INDIRECT_REF);
	  t = TREE_OPERAND (t, 0);
	  gcc_assert (DECL_P (t));
	  omp_add_variable (ctx, t, nflags);
	}

      /* Add all of the variable and type parameters (which should have
	 been gimplified to a formal temporary) as FIRSTPRIVATE.  */
      omp_firstprivatize_variable (ctx, DECL_SIZE_UNIT (decl));
      omp_firstprivatize_variable (ctx, DECL_SIZE (decl));
      omp_firstprivatize_type_sizes (ctx, TREE_TYPE (decl));

      /* The variable-sized variable itself is never SHARED, only some form
	 of PRIVATE.  The sharing would take place via the pointer variable
	 which we remapped above.  */
      if (flags & GOVD_SHARED)
	flags = GOVD_PRIVATE | GOVD_DEBUG_PRIVATE
		| (flags & (GOVD_SEEN | GOVD_EXPLICIT));

      /* We're going to make use of the TYPE_SIZE_UNIT at least in the 
	 alloca statement we generate for the variable, so make sure it
	 is available.  This isn't automatically needed for the SHARED
	 case, since we won't be allocating local storage then.
	 For local variables TYPE_SIZE_UNIT might not be gimplified yet,
	 in this case omp_notice_variable will be called later
	 on when it is gimplified.  */
      else if (! (flags & GOVD_LOCAL))
	omp_notice_variable (ctx, TYPE_SIZE_UNIT (TREE_TYPE (decl)), true);
    }
  else if (lang_hooks.decls.omp_privatize_by_reference (decl))
    {
      gcc_assert ((flags & GOVD_LOCAL) == 0);
      omp_firstprivatize_type_sizes (ctx, TREE_TYPE (decl));

      /* Similar to the direct variable sized case above, we'll need the
	 size of references being privatized.  */
      if ((flags & GOVD_SHARED) == 0)
	{
	  t = TYPE_SIZE_UNIT (TREE_TYPE (TREE_TYPE (decl)));
	  if (TREE_CODE (t) != INTEGER_CST)
	    omp_notice_variable (ctx, t, true);
	}
    }

  splay_tree_insert (ctx->variables, (splay_tree_key)decl, flags);
}