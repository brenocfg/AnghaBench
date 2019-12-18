#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  sbitmap ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {scalar_t__ value; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ SSA_NAME ; 
 size_t SSA_NAME_VERSION (scalar_t__) ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 TYPE_2__* copy_of ; 
 int /*<<< orphan*/  dump_flags ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* get_copy_of_val (scalar_t__) ; 
 int /*<<< orphan*/  num_ssa_names ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_copy_of (FILE *file, tree var)
{
  tree val;
  sbitmap visited;

  print_generic_expr (file, var, dump_flags);

  if (TREE_CODE (var) != SSA_NAME)
    return;
    
  visited = sbitmap_alloc (num_ssa_names);
  sbitmap_zero (visited);
  SET_BIT (visited, SSA_NAME_VERSION (var));
  
  fprintf (file, " copy-of chain: ");

  val = var;
  print_generic_expr (file, val, 0);
  fprintf (file, " ");
  while (copy_of[SSA_NAME_VERSION (val)].value)
    {
      fprintf (file, "-> ");
      val = copy_of[SSA_NAME_VERSION (val)].value;
      print_generic_expr (file, val, 0);
      fprintf (file, " ");
      if (TEST_BIT (visited, SSA_NAME_VERSION (val)))
        break;
      SET_BIT (visited, SSA_NAME_VERSION (val));
    }

  val = get_copy_of_val (var)->value;
  if (val == NULL_TREE)
    fprintf (file, "[UNDEFINED]");
  else if (val != var)
    fprintf (file, "[COPY]");
  else
    fprintf (file, "[NOT A COPY]");
  
  sbitmap_free (visited);
}