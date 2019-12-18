#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rtx ;
typedef  enum attr_itanium_class { ____Placeholder_attr_itanium_class } attr_itanium_class ;
struct TYPE_17__ {int call; } ;

/* Variables and functions */
 TYPE_1__* INSN_DEPEND (TYPE_1__*) ; 
 scalar_t__ INSN_P (TYPE_1__*) ; 
 int ITANIUM_CLASS_FLD ; 
 int ITANIUM_CLASS_FLDP ; 
 scalar_t__ ITANIUM_CLASS_IALU ; 
 int ITANIUM_CLASS_LD ; 
 int ITANIUM_CLASS_ST ; 
 int ITANIUM_CLASS_STF ; 
 TYPE_1__* NEXT_INSN (TYPE_1__*) ; 
 scalar_t__ REG_DEP_TRUE ; 
 scalar_t__ REG_NOTE_KIND (TYPE_1__*) ; 
 TYPE_1__* XEXP (TYPE_1__*,int) ; 
 scalar_t__ ia64_ld_address_bypass_p (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ ia64_safe_itanium_class (TYPE_1__*) ; 
 scalar_t__ ia64_st_address_bypass_p (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  reload_completed ; 

__attribute__((used)) static void
ia64_dependencies_evaluation_hook (rtx head, rtx tail)
{
  rtx insn, link, next, next_tail;

  /* Before reload, which_alternative is not set, which means that
     ia64_safe_itanium_class will produce wrong results for (at least)
     move instructions.  */
  if (!reload_completed)
    return;

  next_tail = NEXT_INSN (tail);
  for (insn = head; insn != next_tail; insn = NEXT_INSN (insn))
    if (INSN_P (insn))
      insn->call = 0;
  for (insn = head; insn != next_tail; insn = NEXT_INSN (insn))
    if (INSN_P (insn)
	&& ia64_safe_itanium_class (insn) == ITANIUM_CLASS_IALU)
      {
	for (link = INSN_DEPEND (insn); link != 0; link = XEXP (link, 1))
	  {
	    enum attr_itanium_class c;

	    if (REG_NOTE_KIND (link) != REG_DEP_TRUE)
	      continue;
	    next = XEXP (link, 0);
	    c = ia64_safe_itanium_class (next);
	    if ((c == ITANIUM_CLASS_ST
		 || c == ITANIUM_CLASS_STF)
		&& ia64_st_address_bypass_p (insn, next))
	      break;
	    else if ((c == ITANIUM_CLASS_LD
		      || c == ITANIUM_CLASS_FLD
		      || c == ITANIUM_CLASS_FLDP)
		     && ia64_ld_address_bypass_p (insn, next))
	      break;
	  }
	insn->call = link != 0;
      }
}