#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_2__* edge ;
struct TYPE_4__ {scalar_t__ r; } ;
struct TYPE_5__ {TYPE_1__ insns; } ;

/* Variables and functions */
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ reg_set_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool
reg_killed_on_edge (rtx reg, edge e)
{
  rtx insn;

  for (insn = e->insns.r; insn; insn = NEXT_INSN (insn))
    if (INSN_P (insn) && reg_set_p (reg, insn))
      return true;

  return false;
}