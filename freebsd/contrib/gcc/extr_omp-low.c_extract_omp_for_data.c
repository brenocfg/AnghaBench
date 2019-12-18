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
typedef  void* tree ;
struct omp_for_data {void* v; int cond_code; void* n2; void* step; int have_nowait; int have_ordered; scalar_t__ sched_kind; int /*<<< orphan*/ * chunk_size; void* for_stmt; void* n1; int /*<<< orphan*/ * pre; } ;

/* Variables and functions */
 int DECL_P (void*) ; 
#define  GE_EXPR 136 
#define  GT_EXPR 135 
 int INTEGER_TYPE ; 
#define  LE_EXPR 134 
#define  LT_EXPR 133 
#define  MINUS_EXPR 132 
 int MODIFY_EXPR ; 
 int /*<<< orphan*/  NEGATE_EXPR ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 void* OMP_CLAUSE_CHAIN (void*) ; 
 int OMP_CLAUSE_CODE (void*) ; 
#define  OMP_CLAUSE_NOWAIT 131 
#define  OMP_CLAUSE_ORDERED 130 
#define  OMP_CLAUSE_SCHEDULE 129 
 int /*<<< orphan*/ * OMP_CLAUSE_SCHEDULE_CHUNK_EXPR (void*) ; 
 scalar_t__ OMP_CLAUSE_SCHEDULE_KIND (void*) ; 
 scalar_t__ OMP_CLAUSE_SCHEDULE_RUNTIME ; 
 scalar_t__ OMP_CLAUSE_SCHEDULE_STATIC ; 
 void* OMP_FOR_CLAUSES (void*) ; 
 void* OMP_FOR_COND (void*) ; 
 void* OMP_FOR_INCR (void*) ; 
 void* OMP_FOR_INIT (void*) ; 
#define  PLUS_EXPR 128 
 int TREE_CODE (void*) ; 
 void* TREE_OPERAND (void*,int) ; 
 void* TREE_TYPE (void*) ; 
 int /*<<< orphan*/  build_int_cst (void*,int) ; 
 void* fold_build1 (int /*<<< orphan*/ ,void*,void*) ; 
 void* fold_build2 (int,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * integer_one_node ; 
 int /*<<< orphan*/ * integer_zero_node ; 

__attribute__((used)) static void
extract_omp_for_data (tree for_stmt, struct omp_for_data *fd)
{
  tree t;

  fd->for_stmt = for_stmt;
  fd->pre = NULL;

  t = OMP_FOR_INIT (for_stmt);
  gcc_assert (TREE_CODE (t) == MODIFY_EXPR);
  fd->v = TREE_OPERAND (t, 0);
  gcc_assert (DECL_P (fd->v));
  gcc_assert (TREE_CODE (TREE_TYPE (fd->v)) == INTEGER_TYPE);
  fd->n1 = TREE_OPERAND (t, 1);

  t = OMP_FOR_COND (for_stmt);
  fd->cond_code = TREE_CODE (t);
  gcc_assert (TREE_OPERAND (t, 0) == fd->v);
  fd->n2 = TREE_OPERAND (t, 1);
  switch (fd->cond_code)
    {
    case LT_EXPR:
    case GT_EXPR:
      break;
    case LE_EXPR:
      fd->n2 = fold_build2 (PLUS_EXPR, TREE_TYPE (fd->n2), fd->n2,
			   build_int_cst (TREE_TYPE (fd->n2), 1));
      fd->cond_code = LT_EXPR;
      break;
    case GE_EXPR:
      fd->n2 = fold_build2 (MINUS_EXPR, TREE_TYPE (fd->n2), fd->n2,
			   build_int_cst (TREE_TYPE (fd->n2), 1));
      fd->cond_code = GT_EXPR;
      break;
    default:
      gcc_unreachable ();
    }

  t = OMP_FOR_INCR (fd->for_stmt);
  gcc_assert (TREE_CODE (t) == MODIFY_EXPR);
  gcc_assert (TREE_OPERAND (t, 0) == fd->v);
  t = TREE_OPERAND (t, 1);
  gcc_assert (TREE_OPERAND (t, 0) == fd->v);
  switch (TREE_CODE (t))
    {
    case PLUS_EXPR:
      fd->step = TREE_OPERAND (t, 1);
      break;
    case MINUS_EXPR:
      fd->step = TREE_OPERAND (t, 1);
      fd->step = fold_build1 (NEGATE_EXPR, TREE_TYPE (fd->step), fd->step);
      break;
    default:
      gcc_unreachable ();
    }

  fd->have_nowait = fd->have_ordered = false;
  fd->sched_kind = OMP_CLAUSE_SCHEDULE_STATIC;
  fd->chunk_size = NULL_TREE;

  for (t = OMP_FOR_CLAUSES (for_stmt); t ; t = OMP_CLAUSE_CHAIN (t))
    switch (OMP_CLAUSE_CODE (t))
      {
      case OMP_CLAUSE_NOWAIT:
	fd->have_nowait = true;
	break;
      case OMP_CLAUSE_ORDERED:
	fd->have_ordered = true;
	break;
      case OMP_CLAUSE_SCHEDULE:
	fd->sched_kind = OMP_CLAUSE_SCHEDULE_KIND (t);
	fd->chunk_size = OMP_CLAUSE_SCHEDULE_CHUNK_EXPR (t);
	break;
      default:
	break;
      }

  if (fd->sched_kind == OMP_CLAUSE_SCHEDULE_RUNTIME)
    gcc_assert (fd->chunk_size == NULL);
  else if (fd->chunk_size == NULL)
    {
      /* We only need to compute a default chunk size for ordered
	 static loops and dynamic loops.  */
      if (fd->sched_kind != OMP_CLAUSE_SCHEDULE_STATIC || fd->have_ordered)
	fd->chunk_size = (fd->sched_kind == OMP_CLAUSE_SCHEDULE_STATIC)
			 ? integer_zero_node : integer_one_node;
    }
}