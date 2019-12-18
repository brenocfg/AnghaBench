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
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;

/* Variables and functions */
 int BUILT_IN_FRAME_ADDRESS ; 
 int BUILT_IN_RETURN_ADDRESS ; 
 int /*<<< orphan*/  DYNAMIC_CHAIN_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FRAME_ADDR_RTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INITIAL_FRAME_ADDRESS_RTX ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  RETURN_ADDR_RTX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP_FRAME_ADDRESSES () ; 
 int /*<<< orphan*/  copy_to_reg (int /*<<< orphan*/ ) ; 
 int current_function_accesses_prior_frames ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 int /*<<< orphan*/  gen_frame_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_return_addr (enum built_in_function fndecl_code, int count)
{
  int i;

#ifdef INITIAL_FRAME_ADDRESS_RTX
  rtx tem = INITIAL_FRAME_ADDRESS_RTX;
#else
  rtx tem;

  /* For a zero count with __builtin_return_address, we don't care what
     frame address we return, because target-specific definitions will
     override us.  Therefore frame pointer elimination is OK, and using
     the soft frame pointer is OK.

     For a non-zero count, or a zero count with __builtin_frame_address,
     we require a stable offset from the current frame pointer to the
     previous one, so we must use the hard frame pointer, and
     we must disable frame pointer elimination.  */
  if (count == 0 && fndecl_code == BUILT_IN_RETURN_ADDRESS)
    tem = frame_pointer_rtx;
  else
    {
      tem = hard_frame_pointer_rtx;

      /* Tell reload not to eliminate the frame pointer.  */
      current_function_accesses_prior_frames = 1;
    }
#endif

  /* Some machines need special handling before we can access
     arbitrary frames.  For example, on the SPARC, we must first flush
     all register windows to the stack.  */
#ifdef SETUP_FRAME_ADDRESSES
  if (count > 0)
    SETUP_FRAME_ADDRESSES ();
#endif

  /* On the SPARC, the return address is not in the frame, it is in a
     register.  There is no way to access it off of the current frame
     pointer, but it can be accessed off the previous frame pointer by
     reading the value from the register window save area.  */
#ifdef RETURN_ADDR_IN_PREVIOUS_FRAME
  if (fndecl_code == BUILT_IN_RETURN_ADDRESS)
    count--;
#endif

  /* Scan back COUNT frames to the specified frame.  */
  for (i = 0; i < count; i++)
    {
      /* Assume the dynamic chain pointer is in the word that the
	 frame address points to, unless otherwise specified.  */
#ifdef DYNAMIC_CHAIN_ADDRESS
      tem = DYNAMIC_CHAIN_ADDRESS (tem);
#endif
      tem = memory_address (Pmode, tem);
      tem = gen_frame_mem (Pmode, tem);
      tem = copy_to_reg (tem);
    }

  /* For __builtin_frame_address, return what we've got.  But, on
     the SPARC for example, we may have to add a bias.  */
  if (fndecl_code == BUILT_IN_FRAME_ADDRESS)
#ifdef FRAME_ADDR_RTX
    return FRAME_ADDR_RTX (tem);
#else
    return tem;
#endif

  /* For __builtin_return_address, get the return address from that frame.  */
#ifdef RETURN_ADDR_RTX
  tem = RETURN_ADDR_RTX (count, tem);
#else
  tem = memory_address (Pmode,
			plus_constant (tem, GET_MODE_SIZE (Pmode)));
  tem = gen_frame_mem (Pmode, tem);
#endif
  return tem;
}