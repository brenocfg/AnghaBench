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

/* Variables and functions */
 scalar_t__ CONSTANT_CLASS_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NONLOCAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_REGISTER (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_ADDRESSABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_STATIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
simple_operand_p (tree exp)
{
  /* Strip any conversions that don't change the machine mode.  */
  STRIP_NOPS (exp);

  return (CONSTANT_CLASS_P (exp)
	  || TREE_CODE (exp) == SSA_NAME
	  || (DECL_P (exp)
	      && ! TREE_ADDRESSABLE (exp)
	      && ! TREE_THIS_VOLATILE (exp)
	      && ! DECL_NONLOCAL (exp)
	      /* Don't regard global variables as simple.  They may be
		 allocated in ways unknown to the compiler (shared memory,
		 #pragma weak, etc).  */
	      && ! TREE_PUBLIC (exp)
	      && ! DECL_EXTERNAL (exp)
	      /* Loading a static variable is unduly expensive, but global
		 registers aren't expensive.  */
	      && (! TREE_STATIC (exp) || DECL_REGISTER (exp))));
}