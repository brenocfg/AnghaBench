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

/* Variables and functions */
 int I387_FCTRL_REGNUM ; 
 scalar_t__ I387_ST0_REGNUM ; 
 int I387_XMM0_REGNUM ; 

int
i386_fpc_regnum_p (int regnum)
{
  if (I387_ST0_REGNUM < 0)
    return 0;

  return (I387_FCTRL_REGNUM <= regnum && regnum < I387_XMM0_REGNUM);
}