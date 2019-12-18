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
struct reg_flags {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int HARD_REGNO_NREGS (int,int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int rws_access_regno (int,struct reg_flags,int) ; 

__attribute__((used)) static int
rws_access_reg (rtx reg, struct reg_flags flags, int pred)
{
  int regno = REGNO (reg);
  int n = HARD_REGNO_NREGS (REGNO (reg), GET_MODE (reg));

  if (n == 1)
    return rws_access_regno (regno, flags, pred);
  else
    {
      int need_barrier = 0;
      while (--n >= 0)
	need_barrier |= rws_access_regno (regno + n, flags, pred);
      return need_barrier;
    }
}