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
struct TYPE_4__ {int /*<<< orphan*/  alias_mayalias; int /*<<< orphan*/  alias_noalias; int /*<<< orphan*/  structnoaddress_resolved; int /*<<< orphan*/  structnoaddress_queries; int /*<<< orphan*/  tbaa_resolved; int /*<<< orphan*/  tbaa_queries; int /*<<< orphan*/  simple_resolved; int /*<<< orphan*/  simple_queries; int /*<<< orphan*/  alias_queries; } ;
struct TYPE_3__ {scalar_t__ symbol_mem_tag; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ PARM_DECL ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ SYMBOL_MEMORY_TAG ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  alias_sets_conflict_p (scalar_t__,scalar_t__) ; 
 TYPE_2__ alias_stats ; 
 int flag_argument_noalias ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ ipa_type_escape_field_does_not_clobber_p (scalar_t__,scalar_t__) ; 
 scalar_t__ ipa_type_escape_star_count_of_interesting_type (scalar_t__) ; 
 scalar_t__ is_global_var (scalar_t__) ; 
 scalar_t__ unmodifiable_var_p (scalar_t__) ; 
 TYPE_1__* var_ann (scalar_t__) ; 

__attribute__((used)) static bool
may_alias_p (tree ptr, HOST_WIDE_INT mem_alias_set,
	     tree var, HOST_WIDE_INT var_alias_set,
	     bool alias_set_only)
{
  tree mem;

  alias_stats.alias_queries++;
  alias_stats.simple_queries++;

  /* By convention, a variable cannot alias itself.  */
  mem = var_ann (ptr)->symbol_mem_tag;
  if (mem == var)
    {
      alias_stats.alias_noalias++;
      alias_stats.simple_resolved++;
      return false;
    }

  /* If -fargument-noalias-global is > 2, pointer arguments may
     not point to anything else.  */
  if (flag_argument_noalias > 2 && TREE_CODE (ptr) == PARM_DECL)
    {
      alias_stats.alias_noalias++;
      alias_stats.simple_resolved++;
      return false;
    }

  /* If -fargument-noalias-global is > 1, pointer arguments may
     not point to global variables.  */
  if (flag_argument_noalias > 1 && is_global_var (var)
      && TREE_CODE (ptr) == PARM_DECL)
    {
      alias_stats.alias_noalias++;
      alias_stats.simple_resolved++;
      return false;
    }

  /* If either MEM or VAR is a read-only global and the other one
     isn't, then PTR cannot point to VAR.  */
  if ((unmodifiable_var_p (mem) && !unmodifiable_var_p (var))
      || (unmodifiable_var_p (var) && !unmodifiable_var_p (mem)))
    {
      alias_stats.alias_noalias++;
      alias_stats.simple_resolved++;
      return false;
    }

  gcc_assert (TREE_CODE (mem) == SYMBOL_MEMORY_TAG);

  alias_stats.tbaa_queries++;

  /* If the alias sets don't conflict then MEM cannot alias VAR.  */
  if (!alias_sets_conflict_p (mem_alias_set, var_alias_set))
    {
      alias_stats.alias_noalias++;
      alias_stats.tbaa_resolved++;
      return false;
    }

  /* If var is a record or union type, ptr cannot point into var
     unless there is some operation explicit address operation in the
     program that can reference a field of the ptr's dereferenced
     type.  This also assumes that the types of both var and ptr are
     contained within the compilation unit, and that there is no fancy
     addressing arithmetic associated with any of the types
     involved.  */

  if ((mem_alias_set != 0) && (var_alias_set != 0))
    {
      tree ptr_type = TREE_TYPE (ptr);
      tree var_type = TREE_TYPE (var);
      
      /* The star count is -1 if the type at the end of the pointer_to 
	 chain is not a record or union type. */ 
      if ((!alias_set_only) && 
	  ipa_type_escape_star_count_of_interesting_type (var_type) >= 0)
	{
	  int ptr_star_count = 0;
	  
	  /* Ipa_type_escape_star_count_of_interesting_type is a little to
	     restrictive for the pointer type, need to allow pointers to
	     primitive types as long as those types cannot be pointers
	     to everything.  */
	  while (POINTER_TYPE_P (ptr_type))
	    /* Strip the *'s off.  */ 
	    {
	      ptr_type = TREE_TYPE (ptr_type);
	      ptr_star_count++;
	    }
	  
	  /* There does not appear to be a better test to see if the 
	     pointer type was one of the pointer to everything 
	     types.  */
	  
	  if (ptr_star_count > 0)
	    {
	      alias_stats.structnoaddress_queries++;
	      if (ipa_type_escape_field_does_not_clobber_p (var_type, 
							    TREE_TYPE (ptr))) 
		{
		  alias_stats.structnoaddress_resolved++;
		  alias_stats.alias_noalias++;
		  return false;
		}
	    }
	  else if (ptr_star_count == 0)
	    {
	      /* If ptr_type was not really a pointer to type, it cannot 
		 alias.  */ 
	      alias_stats.structnoaddress_queries++;
	      alias_stats.structnoaddress_resolved++;
	      alias_stats.alias_noalias++;
	      return false;
	    }
	}
    }

  alias_stats.alias_mayalias++;
  return true;
}