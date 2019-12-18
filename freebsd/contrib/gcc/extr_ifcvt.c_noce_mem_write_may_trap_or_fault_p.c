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
typedef  scalar_t__ rtx ;
struct TYPE_2__ {scalar_t__ (* delegitimize_address ) (scalar_t__) ;} ;

/* Variables and functions */
#define  CONST 138 
 int CONST_INT ; 
 int GET_CODE (scalar_t__) ; 
#define  LABEL_REF 137 
#define  LO_SUM 136 
 scalar_t__ MEM_READONLY_P (scalar_t__) ; 
#define  PLUS 135 
#define  POST_DEC 134 
#define  POST_INC 133 
#define  POST_MODIFY 132 
#define  PRE_DEC 131 
#define  PRE_INC 130 
#define  PRE_MODIFY 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  SYMBOL_REF_DECL (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  decl_readonly_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ may_trap_or_fault_p (scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__) ; 
 TYPE_1__ targetm ; 

__attribute__((used)) static bool
noce_mem_write_may_trap_or_fault_p (rtx mem)
{
  rtx addr;

  if (MEM_READONLY_P (mem))
    return true;

  if (may_trap_or_fault_p (mem))
    return true;

  addr = XEXP (mem, 0);

  /* Call target hook to avoid the effects of -fpic etc....  */
  addr = targetm.delegitimize_address (addr);

  while (addr)
    switch (GET_CODE (addr))
      {
      case CONST:
      case PRE_DEC:
      case PRE_INC:
      case POST_DEC:
      case POST_INC:
      case POST_MODIFY:
	addr = XEXP (addr, 0);
	break;
      case LO_SUM:
      case PRE_MODIFY:
	addr = XEXP (addr, 1);
	break;
      case PLUS:
	if (GET_CODE (XEXP (addr, 1)) == CONST_INT)
	  addr = XEXP (addr, 0);
	else
	  return false;
	break;
      case LABEL_REF:
	return true;
      case SYMBOL_REF:
	if (SYMBOL_REF_DECL (addr)
	    && decl_readonly_section (SYMBOL_REF_DECL (addr), 0))
	  return true;
	return false;
      default:
	return false;
      }

  return false;
}