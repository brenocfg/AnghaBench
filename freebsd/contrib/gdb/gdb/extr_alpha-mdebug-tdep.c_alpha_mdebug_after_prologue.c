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
typedef  scalar_t__ alpha_extra_func_info_t ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ALPHA_SP_REGNUM ; 
 scalar_t__ PROC_FRAME_OFFSET (scalar_t__) ; 
 scalar_t__ PROC_FRAME_REG (scalar_t__) ; 
 int /*<<< orphan*/  alpha_after_prologue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
alpha_mdebug_after_prologue (CORE_ADDR pc, alpha_extra_func_info_t proc_desc)
{
  if (proc_desc)
    {
      /* If function is frameless, then we need to do it the hard way.  I
         strongly suspect that frameless always means prologueless... */
      if (PROC_FRAME_REG (proc_desc) == ALPHA_SP_REGNUM
	  && PROC_FRAME_OFFSET (proc_desc) == 0)
	return 0;
    }

  return alpha_after_prologue (pc);
}