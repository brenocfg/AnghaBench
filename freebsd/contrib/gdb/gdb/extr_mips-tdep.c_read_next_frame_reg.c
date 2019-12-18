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
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int NUM_REGS ; 
 int SP_REGNUM ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  frame_unwind_register_signed (struct frame_info*,int) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  regcache_cooked_read_signed (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static CORE_ADDR
read_next_frame_reg (struct frame_info *fi, int regno)
{
  /* Always a pseudo.  */
  gdb_assert (regno >= NUM_REGS);
  if (fi == NULL)
    {
      LONGEST val;
      regcache_cooked_read_signed (current_regcache, regno, &val);
      return val;
    }
  else if ((regno % NUM_REGS) == SP_REGNUM)
    /* The SP_REGNUM is special, its value is stored in saved_regs.
       In fact, it is so special that it can even only be fetched
       using a raw register number!  Once this code as been converted
       to frame-unwind the problem goes away.  */
    return frame_unwind_register_signed (fi, regno % NUM_REGS);
  else
    return frame_unwind_register_signed (fi, regno);

}