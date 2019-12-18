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
 scalar_t__ BITS_BIG_ENDIAN ; 
 int HOST_CHAR_BIT ; 

__attribute__((used)) static void
move_bits (char *target, int targ_offset, char *source, int src_offset, int n)
{
  unsigned int accum, mask;
  int accum_bits, chunk_size;

  target += targ_offset / HOST_CHAR_BIT;
  targ_offset %= HOST_CHAR_BIT;
  source += src_offset / HOST_CHAR_BIT;
  src_offset %= HOST_CHAR_BIT;
  if (BITS_BIG_ENDIAN)
    {
      accum = (unsigned char) *source;
      source += 1;
      accum_bits = HOST_CHAR_BIT - src_offset;

      while (n > 0)
	{
	  int unused_right;
	  accum = (accum << HOST_CHAR_BIT) + (unsigned char) *source;
	  accum_bits += HOST_CHAR_BIT;
	  source += 1;
	  chunk_size = HOST_CHAR_BIT - targ_offset;
	  if (chunk_size > n)
	    chunk_size = n;
	  unused_right = HOST_CHAR_BIT - (chunk_size + targ_offset);
	  mask = ((1 << chunk_size) - 1) << unused_right;
	  *target =
	    (*target & ~mask)
	    | ((accum >> (accum_bits - chunk_size - unused_right)) & mask);
	  n -= chunk_size;
	  accum_bits -= chunk_size;
	  target += 1;
	  targ_offset = 0;
	}
    }
  else
    {
      accum = (unsigned char) *source >> src_offset;
      source += 1;
      accum_bits = HOST_CHAR_BIT - src_offset;

      while (n > 0)
	{
	  accum = accum + ((unsigned char) *source << accum_bits);
	  accum_bits += HOST_CHAR_BIT;
	  source += 1;
	  chunk_size = HOST_CHAR_BIT - targ_offset;
	  if (chunk_size > n)
	    chunk_size = n;
	  mask = ((1 << chunk_size) - 1) << targ_offset;
	  *target = (*target & ~mask) | ((accum << targ_offset) & mask);
	  n -= chunk_size;
	  accum_bits -= chunk_size;
	  accum >>= chunk_size;
	  target += 1;
	  targ_offset = 0;
	}
    }
}