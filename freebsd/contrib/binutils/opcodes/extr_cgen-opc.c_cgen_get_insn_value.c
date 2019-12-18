#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int bfd_vma ;
struct TYPE_3__ {scalar_t__ insn_endian; int insn_chunk_bitsize; } ;
typedef  int CGEN_INSN_INT ;
typedef  TYPE_1__* CGEN_CPU_DESC ;

/* Variables and functions */
 scalar_t__ CGEN_ENDIAN_BIG ; 
 int /*<<< orphan*/  abort () ; 
 int bfd_get_bits (unsigned char*,int,int) ; 

CGEN_INSN_INT
cgen_get_insn_value (CGEN_CPU_DESC cd, unsigned char *buf, int length)
{
  int big_p = (cd->insn_endian == CGEN_ENDIAN_BIG);
  int insn_chunk_bitsize = cd->insn_chunk_bitsize;
  CGEN_INSN_INT value = 0;

  if (insn_chunk_bitsize != 0 && insn_chunk_bitsize < length)
    {
      /* We need to divide up the incoming value into insn_chunk_bitsize-length
	 segments, and endian-convert them, one at a time. */
      int i;

      /* Enforce divisibility. */ 
      if ((length % insn_chunk_bitsize) != 0)
	abort ();

      for (i = 0; i < length; i += insn_chunk_bitsize) /* NB: i == bits */
	{
	  int index;
	  bfd_vma this_value;
	  index = i; /* NB: not dependent on endianness; opposite of cgen_put_insn_value! */
	  this_value = bfd_get_bits (& buf[index / 8], insn_chunk_bitsize, big_p);
	  value = (value << insn_chunk_bitsize) | this_value;
	}
    }
  else
    {
      value = bfd_get_bits (buf, length, cd->insn_endian == CGEN_ENDIAN_BIG);
    }

  return value;
}