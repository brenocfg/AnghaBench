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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_SPECIAL_POOL_ENTRY_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  CONST 132 
 int /*<<< orphan*/  CONSTANT_POOL_ADDRESS_P (int /*<<< orphan*/ ) ; 
#define  CONST_INT 131 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  MINUS 130 
#define  PLUS 129 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  RS6000_SYMBOL_REF_TLS_P (int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pool_constant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toc_label_name ; 

__attribute__((used)) static int
constant_pool_expr_1 (rtx op, int *have_sym, int *have_toc)
{
  switch (GET_CODE (op))
    {
    case SYMBOL_REF:
      if (RS6000_SYMBOL_REF_TLS_P (op))
	return 0;
      else if (CONSTANT_POOL_ADDRESS_P (op))
	{
	  if (ASM_OUTPUT_SPECIAL_POOL_ENTRY_P (get_pool_constant (op), Pmode))
	    {
	      *have_sym = 1;
	      return 1;
	    }
	  else
	    return 0;
	}
      else if (! strcmp (XSTR (op, 0), toc_label_name))
	{
	  *have_toc = 1;
	  return 1;
	}
      else
	return 0;
    case PLUS:
    case MINUS:
      return (constant_pool_expr_1 (XEXP (op, 0), have_sym, have_toc)
	      && constant_pool_expr_1 (XEXP (op, 1), have_sym, have_toc));
    case CONST:
      return constant_pool_expr_1 (XEXP (op, 0), have_sym, have_toc);
    case CONST_INT:
      return 1;
    default:
      return 0;
    }
}