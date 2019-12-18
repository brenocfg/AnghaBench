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
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__ (* lang_get_callee_fndecl ) (scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ CALL_EXPR ; 
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  STRIP_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_READONLY (scalar_t__) ; 
 int /*<<< orphan*/  TREE_THIS_VOLATILE (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__ lang_hooks ; 
 scalar_t__ stub1 (scalar_t__) ; 

tree
get_callee_fndecl (tree call)
{
  tree addr;

  if (call == error_mark_node)
    return call;

  /* It's invalid to call this function with anything but a
     CALL_EXPR.  */
  gcc_assert (TREE_CODE (call) == CALL_EXPR);

  /* The first operand to the CALL is the address of the function
     called.  */
  addr = TREE_OPERAND (call, 0);

  STRIP_NOPS (addr);

  /* If this is a readonly function pointer, extract its initial value.  */
  if (DECL_P (addr) && TREE_CODE (addr) != FUNCTION_DECL
      && TREE_READONLY (addr) && ! TREE_THIS_VOLATILE (addr)
      && DECL_INITIAL (addr))
    addr = DECL_INITIAL (addr);

  /* If the address is just `&f' for some function `f', then we know
     that `f' is being called.  */
  if (TREE_CODE (addr) == ADDR_EXPR
      && TREE_CODE (TREE_OPERAND (addr, 0)) == FUNCTION_DECL)
    return TREE_OPERAND (addr, 0);

  /* We couldn't figure out what was being called.  Maybe the front
     end has some idea.  */
  return lang_hooks.lang_get_callee_fndecl (call);
}