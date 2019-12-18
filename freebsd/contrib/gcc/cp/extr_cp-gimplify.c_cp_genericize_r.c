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
typedef  int /*<<< orphan*/ * tree ;
struct pointer_set_t {int dummy; } ;
struct cxx_int_tree_map {int /*<<< orphan*/ * to; int /*<<< orphan*/  uid; } ;
struct TYPE_2__ {scalar_t__ extern_decl_map; } ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 int /*<<< orphan*/  CLEANUP_BODY (int /*<<< orphan*/ *) ; 
 scalar_t__ CLEANUP_EH_ONLY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLEANUP_EXPR (int /*<<< orphan*/ *) ; 
 scalar_t__ CLEANUP_STMT ; 
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ *) ; 
 scalar_t__ DECL_THUNK_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ *) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ IS_TYPE_OR_DECL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 scalar_t__ OMP_CLAUSE ; 
 int OMP_CLAUSE_CODE (int /*<<< orphan*/ *) ; 
#define  OMP_CLAUSE_COPYIN 134 
#define  OMP_CLAUSE_COPYPRIVATE 133 
 int /*<<< orphan*/ * OMP_CLAUSE_DECL (int /*<<< orphan*/ *) ; 
#define  OMP_CLAUSE_FIRSTPRIVATE 132 
#define  OMP_CLAUSE_LASTPRIVATE 131 
#define  OMP_CLAUSE_PRIVATE 130 
#define  OMP_CLAUSE_REDUCTION 129 
#define  OMP_CLAUSE_SHARED 128 
 scalar_t__ PARM_DECL ; 
 scalar_t__ RETURN_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRY_CATCH_EXPR ; 
 int /*<<< orphan*/  TRY_FINALLY_EXPR ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/ * build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * convert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert_from_reference (int /*<<< orphan*/ *) ; 
 TYPE_1__* cp_function_chain ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ htab_find_with_hash (scalar_t__,struct cxx_int_tree_map*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_invisiref_parm (int /*<<< orphan*/ *) ; 
 scalar_t__ pointer_set_contains (struct pointer_set_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pointer_set_insert (struct pointer_set_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static tree
cp_genericize_r (tree *stmt_p, int *walk_subtrees, void *data)
{
  tree stmt = *stmt_p;
  struct pointer_set_t *p_set = (struct pointer_set_t*) data;

  if (is_invisiref_parm (stmt)
      /* Don't dereference parms in a thunk, pass the references through. */
      && !(DECL_THUNK_P (current_function_decl)
	   && TREE_CODE (stmt) == PARM_DECL))
    {
      *stmt_p = convert_from_reference (stmt);
      *walk_subtrees = 0;
      return NULL;
    }

  /* Map block scope extern declarations to visible declarations with the
     same name and type in outer scopes if any.  */
  if (cp_function_chain->extern_decl_map
      && (TREE_CODE (stmt) == FUNCTION_DECL || TREE_CODE (stmt) == VAR_DECL)
      && DECL_EXTERNAL (stmt))
    {
      struct cxx_int_tree_map *h, in;
      in.uid = DECL_UID (stmt);
      h = (struct cxx_int_tree_map *)
	  htab_find_with_hash (cp_function_chain->extern_decl_map,
			       &in, in.uid);
      if (h)
	{
	  *stmt_p = h->to;
	  *walk_subtrees = 0;
	  return NULL;
	}
    }

  /* Other than invisiref parms, don't walk the same tree twice.  */
  if (pointer_set_contains (p_set, stmt))
    {
      *walk_subtrees = 0;
      return NULL_TREE;
    }

  if (TREE_CODE (stmt) == ADDR_EXPR
      && is_invisiref_parm (TREE_OPERAND (stmt, 0)))
    {
      *stmt_p = convert (TREE_TYPE (stmt), TREE_OPERAND (stmt, 0));
      *walk_subtrees = 0;
    }
  else if (TREE_CODE (stmt) == RETURN_EXPR
	   && TREE_OPERAND (stmt, 0)
	   && is_invisiref_parm (TREE_OPERAND (stmt, 0)))
    /* Don't dereference an invisiref RESULT_DECL inside a RETURN_EXPR.  */
    *walk_subtrees = 0;
  else if (TREE_CODE (stmt) == OMP_CLAUSE)
    switch (OMP_CLAUSE_CODE (stmt))
      {
      case OMP_CLAUSE_PRIVATE:
      case OMP_CLAUSE_SHARED:
      case OMP_CLAUSE_FIRSTPRIVATE:
      case OMP_CLAUSE_LASTPRIVATE:
      case OMP_CLAUSE_COPYIN:
      case OMP_CLAUSE_COPYPRIVATE:
	/* Don't dereference an invisiref in OpenMP clauses.  */
	if (is_invisiref_parm (OMP_CLAUSE_DECL (stmt)))
	  *walk_subtrees = 0;
	break;
      case OMP_CLAUSE_REDUCTION:
	gcc_assert (!is_invisiref_parm (OMP_CLAUSE_DECL (stmt)));
	break;
      default:
	break;
      }
  else if (IS_TYPE_OR_DECL_P (stmt))
    *walk_subtrees = 0;

  /* Due to the way voidify_wrapper_expr is written, we don't get a chance
     to lower this construct before scanning it, so we need to lower these
     before doing anything else.  */
  else if (TREE_CODE (stmt) == CLEANUP_STMT)
    *stmt_p = build2 (CLEANUP_EH_ONLY (stmt) ? TRY_CATCH_EXPR
					     : TRY_FINALLY_EXPR,
		      void_type_node,
		      CLEANUP_BODY (stmt),
		      CLEANUP_EXPR (stmt));

  pointer_set_insert (p_set, *stmt_p);

  return NULL;
}