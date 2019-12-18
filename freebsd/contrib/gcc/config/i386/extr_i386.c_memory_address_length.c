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
struct ix86_address {scalar_t__ base; scalar_t__ index; scalar_t__ disp; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ POST_INC ; 
 scalar_t__ POST_MODIFY ; 
 scalar_t__ PRE_DEC ; 
 scalar_t__ PRE_MODIFY ; 
 scalar_t__ SUBREG ; 
 void* SUBREG_REG (scalar_t__) ; 
 scalar_t__ arg_pointer_rtx ; 
 scalar_t__ frame_pointer_rtx ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ hard_frame_pointer_rtx ; 
 int ix86_decompose_address (scalar_t__,struct ix86_address*) ; 
 scalar_t__ satisfies_constraint_K (scalar_t__) ; 
 scalar_t__ stack_pointer_rtx ; 

int
memory_address_length (rtx addr)
{
  struct ix86_address parts;
  rtx base, index, disp;
  int len;
  int ok;

  if (GET_CODE (addr) == PRE_DEC
      || GET_CODE (addr) == POST_INC
      || GET_CODE (addr) == PRE_MODIFY
      || GET_CODE (addr) == POST_MODIFY)
    return 0;

  ok = ix86_decompose_address (addr, &parts);
  gcc_assert (ok);

  if (parts.base && GET_CODE (parts.base) == SUBREG)
    parts.base = SUBREG_REG (parts.base);
  if (parts.index && GET_CODE (parts.index) == SUBREG)
    parts.index = SUBREG_REG (parts.index);

  base = parts.base;
  index = parts.index;
  disp = parts.disp;
  len = 0;

  /* Rule of thumb:
       - esp as the base always wants an index,
       - ebp as the base always wants a displacement.  */

  /* Register Indirect.  */
  if (base && !index && !disp)
    {
      /* esp (for its index) and ebp (for its displacement) need
	 the two-byte modrm form.  */
      if (addr == stack_pointer_rtx
	  || addr == arg_pointer_rtx
	  || addr == frame_pointer_rtx
	  || addr == hard_frame_pointer_rtx)
	len = 1;
    }

  /* Direct Addressing.  */
  else if (disp && !base && !index)
    len = 4;

  else
    {
      /* Find the length of the displacement constant.  */
      if (disp)
	{
	  if (base && satisfies_constraint_K (disp))
	    len = 1;
	  else
	    len = 4;
	}
      /* ebp always wants a displacement.  */
      else if (base == hard_frame_pointer_rtx)
        len = 1;

      /* An index requires the two-byte modrm form....  */
      if (index
	  /* ...like esp, which always wants an index.  */
	  || base == stack_pointer_rtx
	  || base == arg_pointer_rtx
	  || base == frame_pointer_rtx)
	len += 1;
    }

  return len;
}