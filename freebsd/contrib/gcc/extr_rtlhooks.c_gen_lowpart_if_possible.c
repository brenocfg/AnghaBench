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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ BYTES_BIG_ENDIAN ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (scalar_t__) ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNITS_PER_WORD ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ adjust_address_nv (scalar_t__,int,int) ; 
 scalar_t__ gen_lowpart_SUBREG (int,scalar_t__) ; 
 scalar_t__ gen_lowpart_common (int,scalar_t__) ; 
 int /*<<< orphan*/  memory_address_p (int,int /*<<< orphan*/ ) ; 

rtx
gen_lowpart_if_possible (enum machine_mode mode, rtx x)
{
  rtx result = gen_lowpart_common (mode, x);

  if (result)
    return result;
  else if (MEM_P (x))
    {
      /* This is the only other case we handle.  */
      int offset = 0;
      rtx new;

      if (WORDS_BIG_ENDIAN)
	offset = (MAX (GET_MODE_SIZE (GET_MODE (x)), UNITS_PER_WORD)
		  - MAX (GET_MODE_SIZE (mode), UNITS_PER_WORD));
      if (BYTES_BIG_ENDIAN)
	/* Adjust the address so that the address-after-the-data is
	   unchanged.  */
	offset -= (MIN (UNITS_PER_WORD, GET_MODE_SIZE (mode))
		   - MIN (UNITS_PER_WORD, GET_MODE_SIZE (GET_MODE (x))));

      new = adjust_address_nv (x, mode, offset);
      if (! memory_address_p (mode, XEXP (new, 0)))
	return 0;

      return new;
    }
  else if (mode != GET_MODE (x) && GET_MODE (x) != VOIDmode)
    return gen_lowpart_SUBREG (mode, x);
  else
    return 0;
}