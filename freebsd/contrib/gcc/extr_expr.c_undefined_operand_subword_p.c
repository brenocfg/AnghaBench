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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ BYTES_BIG_ENDIAN ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int) ; 
 scalar_t__ SUBREG ; 
 int SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 int word_mode ; 

__attribute__((used)) static bool
undefined_operand_subword_p (rtx op, int i)
{
  enum machine_mode innermode, innermostmode;
  int offset;
  if (GET_CODE (op) != SUBREG)
    return false;
  innermode = GET_MODE (op);
  innermostmode = GET_MODE (SUBREG_REG (op));
  offset = i * UNITS_PER_WORD + SUBREG_BYTE (op);
  /* The SUBREG_BYTE represents offset, as if the value were stored in
     memory, except for a paradoxical subreg where we define
     SUBREG_BYTE to be 0; undo this exception as in
     simplify_subreg.  */
  if (SUBREG_BYTE (op) == 0
      && GET_MODE_SIZE (innermostmode) < GET_MODE_SIZE (innermode))
    {
      int difference = (GET_MODE_SIZE (innermostmode) - GET_MODE_SIZE (innermode));
      if (WORDS_BIG_ENDIAN)
	offset += (difference / UNITS_PER_WORD) * UNITS_PER_WORD;
      if (BYTES_BIG_ENDIAN)
	offset += difference % UNITS_PER_WORD;
    }
  if (offset >= GET_MODE_SIZE (innermostmode)
      || offset <= -GET_MODE_SIZE (word_mode))
    return true;
  return false;
}