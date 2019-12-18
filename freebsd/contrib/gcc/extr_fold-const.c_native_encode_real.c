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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 scalar_t__ BYTES_BIG_ENDIAN ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REAL_CST_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 scalar_t__ WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  real_to_target (long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
native_encode_real (tree expr, unsigned char *ptr, int len)
{
  tree type = TREE_TYPE (expr);
  int total_bytes = GET_MODE_SIZE (TYPE_MODE (type));
  int byte, offset, word, words, bitpos;
  unsigned char value;

  /* There are always 32 bits in each long, no matter the size of
     the hosts long.  We handle floating point representations with
     up to 192 bits.  */
  long tmp[6];

  if (total_bytes > len)
    return 0;
  words = 32 / UNITS_PER_WORD;

  real_to_target (tmp, TREE_REAL_CST_PTR (expr), TYPE_MODE (type));

  for (bitpos = 0; bitpos < total_bytes * BITS_PER_UNIT;
       bitpos += BITS_PER_UNIT)
    {
      byte = (bitpos / BITS_PER_UNIT) & 3;
      value = (unsigned char) (tmp[bitpos / 32] >> (bitpos & 31));

      if (UNITS_PER_WORD < 4)
	{
	  word = byte / UNITS_PER_WORD;
	  if (WORDS_BIG_ENDIAN)
	    word = (words - 1) - word;
	  offset = word * UNITS_PER_WORD;
	  if (BYTES_BIG_ENDIAN)
	    offset += (UNITS_PER_WORD - 1) - (byte % UNITS_PER_WORD);
	  else
	    offset += byte % UNITS_PER_WORD;
	}
      else
	offset = BYTES_BIG_ENDIAN ? 3 - byte : byte;
      ptr[offset + ((bitpos / BITS_PER_UNIT) & ~3)] = value;
    }
  return total_bytes;
}