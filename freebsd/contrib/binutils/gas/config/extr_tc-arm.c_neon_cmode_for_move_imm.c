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
typedef  enum neon_el_type { ____Placeholder_neon_el_type } neon_el_type ;

/* Variables and functions */
 int FAIL ; 
 int NT_float ; 
 scalar_t__ is_quarter_float (unsigned int) ; 
 scalar_t__ neon_bits_same_in_bytes (unsigned int) ; 
 unsigned int neon_qfloat_bits (unsigned int) ; 
 int neon_squash_bits (unsigned int) ; 

__attribute__((used)) static int
neon_cmode_for_move_imm (unsigned immlo, unsigned immhi, int float_p,
			 unsigned *immbits, int *op, int size,
			 enum neon_el_type type)
{
  /* Only permit float immediates (including 0.0/-0.0) if the operand type is
     float.  */
  if (type == NT_float && !float_p)
    return FAIL;

  if (type == NT_float && is_quarter_float (immlo) && immhi == 0)
    {
      if (size != 32 || *op == 1)
        return FAIL;
      *immbits = neon_qfloat_bits (immlo);
      return 0xf;
    }

  if (size == 64)
    {
      if (neon_bits_same_in_bytes (immhi)
	  && neon_bits_same_in_bytes (immlo))
	{
	  if (*op == 1)
	    return FAIL;
	  *immbits = (neon_squash_bits (immhi) << 4)
		     | neon_squash_bits (immlo);
	  *op = 1;
	  return 0xe;
	}

      if (immhi != immlo)
	return FAIL;
    }

  if (size >= 32)
    {
      if (immlo == (immlo & 0x000000ff))
	{
	  *immbits = immlo;
	  return 0x0;
	}
      else if (immlo == (immlo & 0x0000ff00))
	{
	  *immbits = immlo >> 8;
	  return 0x2;
	}
      else if (immlo == (immlo & 0x00ff0000))
	{
	  *immbits = immlo >> 16;
	  return 0x4;
	}
      else if (immlo == (immlo & 0xff000000))
	{
	  *immbits = immlo >> 24;
	  return 0x6;
	}
      else if (immlo == ((immlo & 0x0000ff00) | 0x000000ff))
	{
	  *immbits = (immlo >> 8) & 0xff;
	  return 0xc;
	}
      else if (immlo == ((immlo & 0x00ff0000) | 0x0000ffff))
	{
	  *immbits = (immlo >> 16) & 0xff;
	  return 0xd;
	}

      if ((immlo & 0xffff) != (immlo >> 16))
	return FAIL;
      immlo &= 0xffff;
    }

  if (size >= 16)
    {
      if (immlo == (immlo & 0x000000ff))
	{
	  *immbits = immlo;
	  return 0x8;
	}
      else if (immlo == (immlo & 0x0000ff00))
	{
	  *immbits = immlo >> 8;
	  return 0xa;
	}

      if ((immlo & 0xff) != (immlo >> 8))
	return FAIL;
      immlo &= 0xff;
    }

  if (immlo == (immlo & 0x000000ff))
    {
      /* Don't allow MVN with 8-bit immediate.  */
      if (*op == 1)
	return FAIL;
      *immbits = immlo;
      return 0xe;
    }

  return FAIL;
}