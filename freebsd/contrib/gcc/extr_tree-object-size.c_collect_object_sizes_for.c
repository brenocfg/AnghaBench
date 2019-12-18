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
typedef  int /*<<< orphan*/  tree ;
struct object_size_info {int object_size_type; scalar_t__ pass; int /*<<< orphan*/  reexamine; int /*<<< orphan*/  visited; } ;

/* Variables and functions */
#define  ASM_EXPR 132 
 int CALL_EXPR ; 
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int IS_EMPTY_STMT (int /*<<< orphan*/ ) ; 
#define  MODIFY_EXPR 131 
#define  NOP_EXPR 130 
 int PARM_DECL ; 
 int /*<<< orphan*/  PHI_ARG_DEF (int /*<<< orphan*/ ,int) ; 
#define  PHI_NODE 129 
 int PHI_NUM_ARGS (int /*<<< orphan*/ ) ; 
 int PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
#define  RETURN_EXPR 128 
 int SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSA_NAME_VAR (int /*<<< orphan*/ ) ; 
 unsigned int SSA_NAME_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 int TDF_DETAILS ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_clear_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/ * computed ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  expr_object_size (struct object_size_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int merge_object_sizes (struct object_size_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int** object_sizes ; 
 int /*<<< orphan*/  pass_through_call (int /*<<< orphan*/ ) ; 
 int plus_expr_object_size (struct object_size_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int* unknown ; 

__attribute__((used)) static void
collect_object_sizes_for (struct object_size_info *osi, tree var)
{
  int object_size_type = osi->object_size_type;
  unsigned int varno = SSA_NAME_VERSION (var);
  tree stmt;
  bool reexamine;

  if (bitmap_bit_p (computed[object_size_type], varno))
    return;

  if (osi->pass == 0)
    {
      if (! bitmap_bit_p (osi->visited, varno))
	{
	  bitmap_set_bit (osi->visited, varno);
	  object_sizes[object_size_type][varno]
	    = (object_size_type & 2) ? -1 : 0;
	}
      else
	{
	  /* Found a dependency loop.  Mark the variable for later
	     re-examination.  */
	  bitmap_set_bit (osi->reexamine, varno);
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "Found a dependency loop at ");
	      print_generic_expr (dump_file, var, dump_flags);
	      fprintf (dump_file, "\n");
	    }
	  return;
	}
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Visiting use-def links for ");
      print_generic_expr (dump_file, var, dump_flags);
      fprintf (dump_file, "\n");
    }

  stmt = SSA_NAME_DEF_STMT (var);
  reexamine = false;

  switch (TREE_CODE (stmt))
    {
    case RETURN_EXPR:
      gcc_assert (TREE_CODE (TREE_OPERAND (stmt, 0)) == MODIFY_EXPR);
      stmt = TREE_OPERAND (stmt, 0);
      /* FALLTHRU  */

    case MODIFY_EXPR:
      {
	tree rhs = TREE_OPERAND (stmt, 1), arg;
	STRIP_NOPS (rhs);

	if (TREE_CODE (rhs) == CALL_EXPR)
	  {
	    arg = pass_through_call (rhs);
	    if (arg)
	      rhs = arg;
	  }

	if (TREE_CODE (rhs) == SSA_NAME
	    && POINTER_TYPE_P (TREE_TYPE (rhs)))
	  reexamine = merge_object_sizes (osi, var, rhs, 0);

	else if (TREE_CODE (rhs) == PLUS_EXPR)
	  reexamine = plus_expr_object_size (osi, var, rhs);

	else
	  expr_object_size (osi, var, rhs);
	break;
      }

    case ASM_EXPR:
      /* Pointers defined by __asm__ statements can point anywhere.  */
      object_sizes[object_size_type][varno] = unknown[object_size_type];
      break;

    case NOP_EXPR:
      {
	tree decl = SSA_NAME_VAR (var);

	gcc_assert (IS_EMPTY_STMT (stmt));

	if (TREE_CODE (decl) != PARM_DECL && DECL_INITIAL (decl))
	  expr_object_size (osi, var, DECL_INITIAL (decl));
	else
	  expr_object_size (osi, var, decl);
      }
      break;

    case PHI_NODE:
      {
	int i;

	for (i = 0; i < PHI_NUM_ARGS (stmt); i++)
	  {
	    tree rhs = PHI_ARG_DEF (stmt, i);

	    if (object_sizes[object_size_type][varno]
		== unknown[object_size_type])
	      break;

	    if (TREE_CODE (rhs) == SSA_NAME)
	      reexamine |= merge_object_sizes (osi, var, rhs, 0);
	    else if (osi->pass == 0)
	      expr_object_size (osi, var, rhs);
	  }
	break;
      }
    default:
      gcc_unreachable ();
    }

  if (! reexamine
      || object_sizes[object_size_type][varno] == unknown[object_size_type])
    {
      bitmap_set_bit (computed[object_size_type], varno);
      bitmap_clear_bit (osi->reexamine, varno);
    }
  else
    {
      bitmap_set_bit (osi->reexamine, varno);
      if (dump_file && (dump_flags & TDF_DETAILS))
	{
	  fprintf (dump_file, "Need to reexamine ");
	  print_generic_expr (dump_file, var, dump_flags);
	  fprintf (dump_file, "\n");
	}
    }
}