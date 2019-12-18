#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* varinfo_t ;
typedef  scalar_t__ tree ;
struct constraint_expr {unsigned int var; scalar_t__ offset; void* type; } ;
struct TYPE_5__ {unsigned int id; int is_artificial_var; int is_heap_var; int is_unknown_size_var; int directly_dereferenced; struct TYPE_5__* next; } ;
typedef  int DECL_EXTERNAL ;

/* Variables and functions */
 void* ADDRESSOF ; 
 scalar_t__ DECL_ARGUMENTS (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 void* SCALAR ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  add_referenced_var (int) ; 
 int /*<<< orphan*/  could_have_pointers (scalar_t__) ; 
 scalar_t__ create_nonlocal_var (int /*<<< orphan*/ ) ; 
 scalar_t__ create_tmp_var_raw (scalar_t__,char*) ; 
 unsigned int create_variable_info_for (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 unsigned int escaped_vars_id ; 
 int flag_argument_noalias ; 
 int /*<<< orphan*/  get_name (scalar_t__) ; 
 TYPE_1__* get_varinfo (unsigned int) ; 
 TYPE_1__* get_vi_for_tree (scalar_t__) ; 
 int /*<<< orphan*/  heapvar_insert (scalar_t__,int) ; 
 scalar_t__ heapvar_lookup (scalar_t__) ; 
 int /*<<< orphan*/  make_constraint_from_escaped (TYPE_1__*) ; 
 int /*<<< orphan*/  new_constraint (struct constraint_expr,struct constraint_expr) ; 
 scalar_t__ nonlocal_all ; 
 unsigned int nonlocal_vars_id ; 
 int /*<<< orphan*/  process_constraint (int /*<<< orphan*/ ) ; 
 scalar_t__ referenced_vars ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
intra_create_variable_infos (void)
{
  tree t;
  struct constraint_expr lhs, rhs;
  varinfo_t nonlocal_vi;

  /* For each incoming pointer argument arg, ARG = ESCAPED_VARS or a
     dummy variable if flag_argument_noalias > 2. */
  for (t = DECL_ARGUMENTS (current_function_decl); t; t = TREE_CHAIN (t))
    {
      varinfo_t p;
      unsigned int arg_id;
      
      if (!could_have_pointers (t))
	continue;
      
      arg_id = get_vi_for_tree (t)->id;

      /* With flag_argument_noalias greater than two means that the incoming
         argument cannot alias anything except for itself so create a HEAP
         variable.  */
      if (POINTER_TYPE_P (TREE_TYPE (t))
	  && flag_argument_noalias > 2)
	{
	  varinfo_t vi;
	  tree heapvar = heapvar_lookup (t);
	  
	  lhs.offset = 0;
	  lhs.type = SCALAR;
	  lhs.var  = get_vi_for_tree (t)->id;
	  
	  if (heapvar == NULL_TREE)
	    {
	      heapvar = create_tmp_var_raw (TREE_TYPE (TREE_TYPE (t)), 
					    "PARM_NOALIAS");
	      DECL_EXTERNAL (heapvar) = 1;
	      if (referenced_vars)
		add_referenced_var (heapvar);
	      heapvar_insert (t, heapvar);
	    }

	  vi = get_vi_for_tree (heapvar);
	  vi->is_artificial_var = 1;
	  vi->is_heap_var = 1;
	  rhs.var = vi->id;
	  rhs.type = ADDRESSOF;
	  rhs.offset = 0;
          for (p = get_varinfo (lhs.var); p; p = p->next)
	    {
	      struct constraint_expr temp = lhs;
	      temp.var = p->id;
	      process_constraint (new_constraint (temp, rhs));
	    }
	}
      else      
	{
	  for (p = get_varinfo (arg_id); p; p = p->next)
	    make_constraint_from_escaped (p);
	}
    }
  if (!nonlocal_all)
    nonlocal_all = create_nonlocal_var (void_type_node);

  /* Create variable info for the nonlocal var if it does not
     exist.  */
  nonlocal_vars_id = create_variable_info_for (nonlocal_all,
					       get_name (nonlocal_all));
  nonlocal_vi = get_varinfo (nonlocal_vars_id);
  nonlocal_vi->is_artificial_var = 1;
  nonlocal_vi->is_heap_var = 1; 
  nonlocal_vi->is_unknown_size_var = 1;
  nonlocal_vi->directly_dereferenced = true;

  rhs.var = nonlocal_vars_id;
  rhs.type = ADDRESSOF;
  rhs.offset = 0;
  
  lhs.var = escaped_vars_id;
  lhs.type = SCALAR;
  lhs.offset = 0;
  
  process_constraint (new_constraint (lhs, rhs));
}