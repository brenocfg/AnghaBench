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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ INSN_DEPEND (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int insn_cost (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ rs6000_is_costly_dependence (scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int rs6000_issue_rate () ; 

__attribute__((used)) static bool
is_costly_group (rtx *group_insns, rtx next_insn)
{
  int i;
  rtx link;
  int cost;
  int issue_rate = rs6000_issue_rate ();

  for (i = 0; i < issue_rate; i++)
    {
      rtx insn = group_insns[i];
      if (!insn)
	continue;
      for (link = INSN_DEPEND (insn); link != 0; link = XEXP (link, 1))
	{
	  rtx next = XEXP (link, 0);
	  if (next == next_insn)
	    {
	      cost = insn_cost (insn, link, next_insn);
	      if (rs6000_is_costly_dependence (insn, next_insn, link, cost, 0))
		return true;
	    }
	}
    }

  return false;
}