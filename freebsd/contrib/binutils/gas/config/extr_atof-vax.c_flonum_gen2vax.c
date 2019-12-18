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
struct TYPE_3__ {scalar_t__ low; scalar_t__ leader; char sign; long exponent; } ;
typedef  unsigned long LITTLENUM_TYPE ;
typedef  TYPE_1__ FLONUM_TYPE ;

/* Variables and functions */
 long LITTLENUM_NUMBER_OF_BITS ; 
 long bits_left_in_littlenum ; 
 scalar_t__ littlenum_end ; 
 scalar_t__ littlenum_pointer ; 
 int /*<<< orphan*/  make_invalid_floating_point_number (unsigned long*) ; 
 long* mask ; 
 int /*<<< orphan*/  memset (unsigned long*,char,int) ; 
 int next_bits (int) ; 
 int what_kind_of_float (int,int*,long*) ; 

int
flonum_gen2vax (int format_letter,	/* One of 'd' 'f' 'g' 'h'.  */
		FLONUM_TYPE *f,
		LITTLENUM_TYPE *words)	/* Deliver answer here.  */
{
  LITTLENUM_TYPE *lp;
  int precision;
  long exponent_bits;
  int return_value;		/* 0 == OK.  */

  return_value = what_kind_of_float (format_letter, &precision, &exponent_bits);

  if (return_value != 0)
    make_invalid_floating_point_number (words);

  else
    {
      if (f->low > f->leader)
	/* 0.0e0 seen.  */
	memset (words, '\0', sizeof (LITTLENUM_TYPE) * precision);

      else
	{
	  long exponent_1;
	  long exponent_2;
	  long exponent_3;
	  long exponent_4;
	  int exponent_skippage;
	  LITTLENUM_TYPE word1;

	  /* JF: Deal with new Nan, +Inf and -Inf codes.  */
	  if (f->sign != '-' && f->sign != '+')
	    {
	      make_invalid_floating_point_number (words);
	      return return_value;
	    }

	  /* All vaxen floating_point formats (so far) have:
	     Bit 15 is sign bit.
	     Bits 14:n are excess-whatever exponent.
	     Bits n-1:0 (if any) are most significant bits of fraction.
	     Bits 15:0 of the next word are the next most significant bits.
	     And so on for each other word.

	     All this to be compatible with a KF11?? (Which is still faster
	     than lots of vaxen I can think of, but it also has higher
	     maintenance costs ... sigh).

	     So we need: number of bits of exponent, number of bits of
	     mantissa.  */

	  bits_left_in_littlenum = LITTLENUM_NUMBER_OF_BITS;
	  littlenum_pointer = f->leader;
	  littlenum_end = f->low;
	  /* Seek (and forget) 1st significant bit.  */
	  for (exponent_skippage = 0;
	       !next_bits (1);
	       exponent_skippage++);;

	  exponent_1 = f->exponent + f->leader + 1 - f->low;
	  /* Radix LITTLENUM_RADIX, point just higher than f->leader.  */
	  exponent_2 = exponent_1 * LITTLENUM_NUMBER_OF_BITS;
	  /* Radix 2.  */
	  exponent_3 = exponent_2 - exponent_skippage;
	  /* Forget leading zeros, forget 1st bit.  */
	  exponent_4 = exponent_3 + (1 << (exponent_bits - 1));
	  /* Offset exponent.  */

	  if (exponent_4 & ~mask[exponent_bits])
	    {
	      /* Exponent overflow. Lose immediately.  */
	      make_invalid_floating_point_number (words);

	      /* We leave return_value alone: admit we read the
	         number, but return a floating exception
	         because we can't encode the number.  */
	    }
	  else
	    {
	      lp = words;

	      /* Word 1. Sign, exponent and perhaps high bits.
	         Assume 2's complement integers.  */
	      word1 = (((exponent_4 & mask[exponent_bits]) << (15 - exponent_bits))
		       | ((f->sign == '+') ? 0 : 0x8000)
		       | next_bits (15 - exponent_bits));
	      *lp++ = word1;

	      /* The rest of the words are just mantissa bits.  */
	      for (; lp < words + precision; lp++)
		*lp = next_bits (LITTLENUM_NUMBER_OF_BITS);

	      if (next_bits (1))
		{
		  /* Since the NEXT bit is a 1, round UP the mantissa.
		     The cunning design of these hidden-1 floats permits
		     us to let the mantissa overflow into the exponent, and
		     it 'does the right thing'. However, we lose if the
		     highest-order bit of the lowest-order word flips.
		     Is that clear?  */
		  unsigned long carry;

		  /*
		    #if (sizeof(carry)) < ((sizeof(bits[0]) * BITS_PER_CHAR) + 2)
		    Please allow at least 1 more bit in carry than is in a LITTLENUM.
		    We need that extra bit to hold a carry during a LITTLENUM carry
		    propagation. Another extra bit (kept 0) will assure us that we
		    don't get a sticky sign bit after shifting right, and that
		    permits us to propagate the carry without any masking of bits.
		    #endif   */
		  for (carry = 1, lp--;
		       carry && (lp >= words);
		       lp--)
		    {
		      carry = *lp + carry;
		      *lp = carry;
		      carry >>= LITTLENUM_NUMBER_OF_BITS;
		    }

		  if ((word1 ^ *words) & (1 << (LITTLENUM_NUMBER_OF_BITS - 1)))
		    {
		      make_invalid_floating_point_number (words);
		      /* We leave return_value alone: admit we read the
		         number, but return a floating exception
		         because we can't encode the number.  */
		    }
		}
	    }
	}
    }
  return return_value;
}