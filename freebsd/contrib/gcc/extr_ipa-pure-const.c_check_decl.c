#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* funct_state ;
struct TYPE_3__ {scalar_t__ pure_const_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ IPA_CONST ; 
 void* IPA_NEITHER ; 
 void* IPA_PURE ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_READONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STATIC (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void 
check_decl (funct_state local, 
	    tree t, bool checking_write)
{
  /* If the variable has the "used" attribute, treat it as if it had a
     been touched by the devil.  */
  if (lookup_attribute ("used", DECL_ATTRIBUTES (t)))
    {
      local->pure_const_state = IPA_NEITHER;
      return;
    }

  /* Do not want to do anything with volatile except mark any
     function that uses one to be not const or pure.  */
  if (TREE_THIS_VOLATILE (t)) 
    { 
      local->pure_const_state = IPA_NEITHER;
      return;
    }

  /* Do not care about a local automatic that is not static.  */
  if (!TREE_STATIC (t) && !DECL_EXTERNAL (t))
    return;

  /* Since we have dealt with the locals and params cases above, if we
     are CHECKING_WRITE, this cannot be a pure or constant
     function.  */
  if (checking_write) 
    local->pure_const_state = IPA_NEITHER;

  if (DECL_EXTERNAL (t) || TREE_PUBLIC (t))
    {
      /* If the front end set the variable to be READONLY and
	 constant, we can allow this variable in pure or const
	 functions but the scope is too large for our analysis to set
	 these bits ourselves.  */
      
      if (TREE_READONLY (t)
	  && DECL_INITIAL (t)
	  && is_gimple_min_invariant (DECL_INITIAL (t)))
	; /* Read of a constant, do not change the function state.  */
      else 
	{
	  /* Just a regular read.  */
	  if (local->pure_const_state == IPA_CONST)
	    local->pure_const_state = IPA_PURE;
	}
    }
  
  /* Compilation level statics can be read if they are readonly
     variables.  */
  if (TREE_READONLY (t))
    return;

  /* Just a regular read.  */
  if (local->pure_const_state == IPA_CONST)
    local->pure_const_state = IPA_PURE;
}