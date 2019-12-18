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
struct data_reference {int dummy; } ;

/* Variables and functions */
 scalar_t__ COMPONENT_REF ; 
 int /*<<< orphan*/  DR_BASE_OBJECT (struct data_reference*) ; 
 scalar_t__ INDIRECT_REF ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ ptr_decl_may_alias_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct data_reference*,int*) ; 
 scalar_t__ ptr_ptr_may_alias_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct data_reference*,struct data_reference*,int*) ; 

__attribute__((used)) static bool
record_ptr_differ_p (struct data_reference *dra,
		     struct data_reference *drb)
{
  bool aliased;
  tree base_a = DR_BASE_OBJECT (dra);
  tree base_b = DR_BASE_OBJECT (drb);

  if (TREE_CODE (base_b) != COMPONENT_REF)
    return false;

  /* Peel COMPONENT_REFs to get to the base. Do not peel INDIRECT_REFs.
     For a.b.c.d[i] we will get a, and for a.b->c.d[i] we will get a.b.  
     Probably will be unnecessary with struct alias analysis.  */
  while (TREE_CODE (base_b) == COMPONENT_REF)
     base_b = TREE_OPERAND (base_b, 0);
  /* Compare a record/union access (b.c[i] or p->c[i]) and a pointer
     ((*q)[i]).  */
  if (TREE_CODE (base_a) == INDIRECT_REF
      && ((TREE_CODE (base_b) == VAR_DECL
	   && (ptr_decl_may_alias_p (TREE_OPERAND (base_a, 0), base_b, dra, 
				     &aliased)
	       && !aliased))
	  || (TREE_CODE (base_b) == INDIRECT_REF
	      && (ptr_ptr_may_alias_p (TREE_OPERAND (base_a, 0), 
				       TREE_OPERAND (base_b, 0), dra, drb, 
				       &aliased)
		  && !aliased))))
    return true;
  else
    return false;
}