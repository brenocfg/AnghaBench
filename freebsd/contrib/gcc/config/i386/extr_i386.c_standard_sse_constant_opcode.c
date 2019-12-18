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
 int /*<<< orphan*/  MODE_V2DF ; 
 int /*<<< orphan*/  MODE_V4SF ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_attr_mode (int /*<<< orphan*/ ) ; 
 int standard_sse_constant_p (int /*<<< orphan*/ ) ; 

const char *
standard_sse_constant_opcode (rtx insn, rtx x)
{
  switch (standard_sse_constant_p (x))
    {
    case 1:
      if (get_attr_mode (insn) == MODE_V4SF)
        return "xorps\t%0, %0";
      else if (get_attr_mode (insn) == MODE_V2DF)
        return "xorpd\t%0, %0";
      else
        return "pxor\t%0, %0";
    case 2:
      return "pcmpeqd\t%0, %0";
    }
  gcc_unreachable ();
}