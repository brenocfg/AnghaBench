#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int valueT ;
typedef  int offsetT ;
struct TYPE_5__ {scalar_t__ X_op; int X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_HI16 ; 
 int BFD_RELOC_LO16 ; 
 int COUNT_TOP_ZEROES (unsigned int) ; 
 scalar_t__ HAVE_32BIT_GPRS ; 
 scalar_t__ IS_SEXT_16BIT_NUM (int) ; 
 scalar_t__ IS_SEXT_32BIT_NUM (int) ; 
 scalar_t__ O_big ; 
 scalar_t__ O_constant ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int* generic_bignum ; 
 int /*<<< orphan*/  macro_build (TYPE_1__*,char*,char*,int,int,...) ; 
 int /*<<< orphan*/  normalize_constant_expr (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf_vma (char*,int) ; 

__attribute__((used)) static void
load_register (int reg, expressionS *ep, int dbl)
{
  int freg;
  expressionS hi32, lo32;

  if (ep->X_op != O_big)
    {
      assert (ep->X_op == O_constant);

      /* Sign-extending 32-bit constants makes their handling easier.  */
      if (!dbl)
	normalize_constant_expr (ep);

      if (IS_SEXT_16BIT_NUM (ep->X_add_number))
	{
	  /* We can handle 16 bit signed values with an addiu to
	     $zero.  No need to ever use daddiu here, since $zero and
	     the result are always correct in 32 bit mode.  */
	  macro_build (ep, "addiu", "t,r,j", reg, 0, BFD_RELOC_LO16);
	  return;
	}
      else if (ep->X_add_number >= 0 && ep->X_add_number < 0x10000)
	{
	  /* We can handle 16 bit unsigned values with an ori to
             $zero.  */
	  macro_build (ep, "ori", "t,r,i", reg, 0, BFD_RELOC_LO16);
	  return;
	}
      else if ((IS_SEXT_32BIT_NUM (ep->X_add_number)))
	{
	  /* 32 bit values require an lui.  */
	  macro_build (ep, "lui", "t,u", reg, BFD_RELOC_HI16);
	  if ((ep->X_add_number & 0xffff) != 0)
	    macro_build (ep, "ori", "t,r,i", reg, reg, BFD_RELOC_LO16);
	  return;
	}
    }

  /* The value is larger than 32 bits.  */

  if (!dbl || HAVE_32BIT_GPRS)
    {
      char value[32];

      sprintf_vma (value, ep->X_add_number);
      as_bad (_("Number (0x%s) larger than 32 bits"), value);
      macro_build (ep, "addiu", "t,r,j", reg, 0, BFD_RELOC_LO16);
      return;
    }

  if (ep->X_op != O_big)
    {
      hi32 = *ep;
      hi32.X_add_number = (valueT) hi32.X_add_number >> 16;
      hi32.X_add_number = (valueT) hi32.X_add_number >> 16;
      hi32.X_add_number &= 0xffffffff;
      lo32 = *ep;
      lo32.X_add_number &= 0xffffffff;
    }
  else
    {
      assert (ep->X_add_number > 2);
      if (ep->X_add_number == 3)
	generic_bignum[3] = 0;
      else if (ep->X_add_number > 4)
	as_bad (_("Number larger than 64 bits"));
      lo32.X_op = O_constant;
      lo32.X_add_number = generic_bignum[0] + (generic_bignum[1] << 16);
      hi32.X_op = O_constant;
      hi32.X_add_number = generic_bignum[2] + (generic_bignum[3] << 16);
    }

  if (hi32.X_add_number == 0)
    freg = 0;
  else
    {
      int shift, bit;
      unsigned long hi, lo;

      if (hi32.X_add_number == (offsetT) 0xffffffff)
	{
	  if ((lo32.X_add_number & 0xffff8000) == 0xffff8000)
	    {
	      macro_build (&lo32, "addiu", "t,r,j", reg, 0, BFD_RELOC_LO16);
	      return;
	    }
	  if (lo32.X_add_number & 0x80000000)
	    {
	      macro_build (&lo32, "lui", "t,u", reg, BFD_RELOC_HI16);
	      if (lo32.X_add_number & 0xffff)
		macro_build (&lo32, "ori", "t,r,i", reg, reg, BFD_RELOC_LO16);
	      return;
	    }
	}

      /* Check for 16bit shifted constant.  We know that hi32 is
         non-zero, so start the mask on the first bit of the hi32
         value.  */
      shift = 17;
      do
	{
	  unsigned long himask, lomask;

	  if (shift < 32)
	    {
	      himask = 0xffff >> (32 - shift);
	      lomask = (0xffff << shift) & 0xffffffff;
	    }
	  else
	    {
	      himask = 0xffff << (shift - 32);
	      lomask = 0;
	    }
	  if ((hi32.X_add_number & ~(offsetT) himask) == 0
	      && (lo32.X_add_number & ~(offsetT) lomask) == 0)
	    {
	      expressionS tmp;

	      tmp.X_op = O_constant;
	      if (shift < 32)
		tmp.X_add_number = ((hi32.X_add_number << (32 - shift))
				    | (lo32.X_add_number >> shift));
	      else
		tmp.X_add_number = hi32.X_add_number >> (shift - 32);
	      macro_build (&tmp, "ori", "t,r,i", reg, 0, BFD_RELOC_LO16);
	      macro_build (NULL, (shift >= 32) ? "dsll32" : "dsll", "d,w,<",
			   reg, reg, (shift >= 32) ? shift - 32 : shift);
	      return;
	    }
	  ++shift;
	}
      while (shift <= (64 - 16));

      /* Find the bit number of the lowest one bit, and store the
         shifted value in hi/lo.  */
      hi = (unsigned long) (hi32.X_add_number & 0xffffffff);
      lo = (unsigned long) (lo32.X_add_number & 0xffffffff);
      if (lo != 0)
	{
	  bit = 0;
	  while ((lo & 1) == 0)
	    {
	      lo >>= 1;
	      ++bit;
	    }
	  lo |= (hi & (((unsigned long) 1 << bit) - 1)) << (32 - bit);
	  hi >>= bit;
	}
      else
	{
	  bit = 32;
	  while ((hi & 1) == 0)
	    {
	      hi >>= 1;
	      ++bit;
	    }
	  lo = hi;
	  hi = 0;
	}

      /* Optimize if the shifted value is a (power of 2) - 1.  */
      if ((hi == 0 && ((lo + 1) & lo) == 0)
	  || (lo == 0xffffffff && ((hi + 1) & hi) == 0))
	{
	  shift = COUNT_TOP_ZEROES ((unsigned int) hi32.X_add_number);
	  if (shift != 0)
	    {
	      expressionS tmp;

	      /* This instruction will set the register to be all
                 ones.  */
	      tmp.X_op = O_constant;
	      tmp.X_add_number = (offsetT) -1;
	      macro_build (&tmp, "addiu", "t,r,j", reg, 0, BFD_RELOC_LO16);
	      if (bit != 0)
		{
		  bit += shift;
		  macro_build (NULL, (bit >= 32) ? "dsll32" : "dsll", "d,w,<",
			       reg, reg, (bit >= 32) ? bit - 32 : bit);
		}
	      macro_build (NULL, (shift >= 32) ? "dsrl32" : "dsrl", "d,w,<",
			   reg, reg, (shift >= 32) ? shift - 32 : shift);
	      return;
	    }
	}

      /* Sign extend hi32 before calling load_register, because we can
         generally get better code when we load a sign extended value.  */
      if ((hi32.X_add_number & 0x80000000) != 0)
	hi32.X_add_number |= ~(offsetT) 0xffffffff;
      load_register (reg, &hi32, 0);
      freg = reg;
    }
  if ((lo32.X_add_number & 0xffff0000) == 0)
    {
      if (freg != 0)
	{
	  macro_build (NULL, "dsll32", "d,w,<", reg, freg, 0);
	  freg = reg;
	}
    }
  else
    {
      expressionS mid16;

      if ((freg == 0) && (lo32.X_add_number == (offsetT) 0xffffffff))
	{
	  macro_build (&lo32, "lui", "t,u", reg, BFD_RELOC_HI16);
	  macro_build (NULL, "dsrl32", "d,w,<", reg, reg, 0);
	  return;
	}

      if (freg != 0)
	{
	  macro_build (NULL, "dsll", "d,w,<", reg, freg, 16);
	  freg = reg;
	}
      mid16 = lo32;
      mid16.X_add_number >>= 16;
      macro_build (&mid16, "ori", "t,r,i", reg, freg, BFD_RELOC_LO16);
      macro_build (NULL, "dsll", "d,w,<", reg, reg, 16);
      freg = reg;
    }
  if ((lo32.X_add_number & 0xffff) != 0)
    macro_build (&lo32, "ori", "t,r,i", reg, freg, BFD_RELOC_LO16);
}