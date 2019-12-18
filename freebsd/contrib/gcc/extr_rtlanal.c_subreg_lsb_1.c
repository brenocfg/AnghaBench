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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 unsigned int BITS_PER_UNIT ; 
 unsigned int BITS_PER_WORD ; 
 scalar_t__ BYTES_BIG_ENDIAN ; 
 scalar_t__ GET_MODE_BITSIZE (int) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 unsigned int UNITS_PER_WORD ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

unsigned int
subreg_lsb_1 (enum machine_mode outer_mode,
	      enum machine_mode inner_mode,
	      unsigned int subreg_byte)
{
  unsigned int bitpos;
  unsigned int byte;
  unsigned int word;

  /* A paradoxical subreg begins at bit position 0.  */
  if (GET_MODE_BITSIZE (outer_mode) > GET_MODE_BITSIZE (inner_mode))
    return 0;

  if (WORDS_BIG_ENDIAN != BYTES_BIG_ENDIAN)
    /* If the subreg crosses a word boundary ensure that
       it also begins and ends on a word boundary.  */
    gcc_assert (!((subreg_byte % UNITS_PER_WORD
		  + GET_MODE_SIZE (outer_mode)) > UNITS_PER_WORD
		  && (subreg_byte % UNITS_PER_WORD
		      || GET_MODE_SIZE (outer_mode) % UNITS_PER_WORD)));

  if (WORDS_BIG_ENDIAN)
    word = (GET_MODE_SIZE (inner_mode)
	    - (subreg_byte + GET_MODE_SIZE (outer_mode))) / UNITS_PER_WORD;
  else
    word = subreg_byte / UNITS_PER_WORD;
  bitpos = word * BITS_PER_WORD;

  if (BYTES_BIG_ENDIAN)
    byte = (GET_MODE_SIZE (inner_mode)
	    - (subreg_byte + GET_MODE_SIZE (outer_mode))) % UNITS_PER_WORD;
  else
    byte = subreg_byte % UNITS_PER_WORD;
  bitpos += byte * BITS_PER_UNIT;

  return bitpos;
}