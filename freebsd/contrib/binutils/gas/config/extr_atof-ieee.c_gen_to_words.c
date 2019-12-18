#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ low; scalar_t__ leader; char sign; long exponent; } ;
typedef  unsigned long LITTLENUM_TYPE ;

/* Variables and functions */
 int F_PRECISION ; 
 long LITTLENUM_NUMBER_OF_BITS ; 
 scalar_t__ TC_LARGEST_EXPONENT_IS_NORMAL (int) ; 
 int X_PRECISION ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_warn (char*) ; 
 long bits_left_in_littlenum ; 
 TYPE_1__ generic_floating_point_number ; 
 scalar_t__ littlenum_pointer ; 
 scalar_t__ littlenums_left ; 
 int /*<<< orphan*/  make_invalid_floating_point_number (unsigned long*) ; 
 unsigned long* mask ; 
 int /*<<< orphan*/  memset (unsigned long*,char,int) ; 
 int next_bits (int) ; 
 int /*<<< orphan*/  unget_bits (int) ; 

int
gen_to_words (LITTLENUM_TYPE *words, int precision, long exponent_bits)
{
  int return_value = 0;

  long exponent_1;
  long exponent_2;
  long exponent_3;
  long exponent_4;
  int exponent_skippage;
  LITTLENUM_TYPE word1;
  LITTLENUM_TYPE *lp;
  LITTLENUM_TYPE *words_end;

  words_end = words + precision;
#ifdef TC_M68K
  if (precision == X_PRECISION)
    /* On the m68k the extended precision format has a gap of 16 bits
       between the exponent and the mantissa.  */
    words_end++;
#endif

  if (generic_floating_point_number.low > generic_floating_point_number.leader)
    {
      /* 0.0e0 seen.  */
      if (generic_floating_point_number.sign == '+')
	words[0] = 0x0000;
      else
	words[0] = 0x8000;
      memset (&words[1], '\0',
	      (words_end - words - 1) * sizeof (LITTLENUM_TYPE));
      return return_value;
    }

  /* NaN:  Do the right thing.  */
  if (generic_floating_point_number.sign == 0)
    {
      if (TC_LARGEST_EXPONENT_IS_NORMAL (precision))
	as_warn ("NaNs are not supported by this target\n");
      if (precision == F_PRECISION)
	{
	  words[0] = 0x7fff;
	  words[1] = 0xffff;
	}
      else if (precision == X_PRECISION)
	{
#ifdef TC_M68K
	  words[0] = 0x7fff;
	  words[1] = 0;
	  words[2] = 0xffff;
	  words[3] = 0xffff;
	  words[4] = 0xffff;
	  words[5] = 0xffff;
#else /* ! TC_M68K  */
#ifdef TC_I386
	  words[0] = 0xffff;
	  words[1] = 0xc000;
	  words[2] = 0;
	  words[3] = 0;
	  words[4] = 0;
#else /* ! TC_I386  */
	  abort ();
#endif /* ! TC_I386  */
#endif /* ! TC_M68K  */
	}
      else
	{
	  words[0] = 0x7fff;
	  words[1] = 0xffff;
	  words[2] = 0xffff;
	  words[3] = 0xffff;
	}
      return return_value;
    }
  else if (generic_floating_point_number.sign == 'P')
    {
      if (TC_LARGEST_EXPONENT_IS_NORMAL (precision))
	as_warn ("Infinities are not supported by this target\n");

      /* +INF:  Do the right thing.  */
      if (precision == F_PRECISION)
	{
	  words[0] = 0x7f80;
	  words[1] = 0;
	}
      else if (precision == X_PRECISION)
	{
#ifdef TC_M68K
	  words[0] = 0x7fff;
	  words[1] = 0;
	  words[2] = 0;
	  words[3] = 0;
	  words[4] = 0;
	  words[5] = 0;
#else /* ! TC_M68K  */
#ifdef TC_I386
	  words[0] = 0x7fff;
	  words[1] = 0x8000;
	  words[2] = 0;
	  words[3] = 0;
	  words[4] = 0;
#else /* ! TC_I386  */
	  abort ();
#endif /* ! TC_I386  */
#endif /* ! TC_M68K  */
	}
      else
	{
	  words[0] = 0x7ff0;
	  words[1] = 0;
	  words[2] = 0;
	  words[3] = 0;
	}
      return return_value;
    }
  else if (generic_floating_point_number.sign == 'N')
    {
      if (TC_LARGEST_EXPONENT_IS_NORMAL (precision))
	as_warn ("Infinities are not supported by this target\n");

      /* Negative INF.  */
      if (precision == F_PRECISION)
	{
	  words[0] = 0xff80;
	  words[1] = 0x0;
	}
      else if (precision == X_PRECISION)
	{
#ifdef TC_M68K
	  words[0] = 0xffff;
	  words[1] = 0;
	  words[2] = 0;
	  words[3] = 0;
	  words[4] = 0;
	  words[5] = 0;
#else /* ! TC_M68K  */
#ifdef TC_I386
	  words[0] = 0xffff;
	  words[1] = 0x8000;
	  words[2] = 0;
	  words[3] = 0;
	  words[4] = 0;
#else /* ! TC_I386  */
	  abort ();
#endif /* ! TC_I386  */
#endif /* ! TC_M68K  */
	}
      else
	{
	  words[0] = 0xfff0;
	  words[1] = 0x0;
	  words[2] = 0x0;
	  words[3] = 0x0;
	}
      return return_value;
    }

  /* The floating point formats we support have:
     Bit 15 is sign bit.
     Bits 14:n are excess-whatever exponent.
     Bits n-1:0 (if any) are most significant bits of fraction.
     Bits 15:0 of the next word(s) are the next most significant bits.

     So we need: number of bits of exponent, number of bits of
     mantissa.  */
  bits_left_in_littlenum = LITTLENUM_NUMBER_OF_BITS;
  littlenum_pointer = generic_floating_point_number.leader;
  littlenums_left = (1
		     + generic_floating_point_number.leader
		     - generic_floating_point_number.low);

  /* Seek (and forget) 1st significant bit.  */
  for (exponent_skippage = 0; !next_bits (1); ++exponent_skippage)
	;;
  exponent_1 = (generic_floating_point_number.exponent
		+ generic_floating_point_number.leader
		+ 1
		- generic_floating_point_number.low);

  /* Radix LITTLENUM_RADIX, point just higher than
     generic_floating_point_number.leader.  */
  exponent_2 = exponent_1 * LITTLENUM_NUMBER_OF_BITS;

  /* Radix 2.  */
  exponent_3 = exponent_2 - exponent_skippage;

  /* Forget leading zeros, forget 1st bit.  */
  exponent_4 = exponent_3 + ((1 << (exponent_bits - 1)) - 2);

  /* Offset exponent.  */
  lp = words;

  /* Word 1.  Sign, exponent and perhaps high bits.  */
  word1 = ((generic_floating_point_number.sign == '+')
	   ? 0
	   : (1 << (LITTLENUM_NUMBER_OF_BITS - 1)));

  /* Assume 2's complement integers.  */
  if (exponent_4 <= 0)
    {
      int prec_bits;
      int num_bits;

      unget_bits (1);
      num_bits = -exponent_4;
      prec_bits =
	LITTLENUM_NUMBER_OF_BITS * precision - (exponent_bits + 1 + num_bits);
#ifdef TC_I386
      if (precision == X_PRECISION && exponent_bits == 15)
	{
	  /* On the i386 a denormalized extended precision float is
	     shifted down by one, effectively decreasing the exponent
	     bias by one.  */
	  prec_bits -= 1;
	  num_bits += 1;
	}
#endif

      if (num_bits >= LITTLENUM_NUMBER_OF_BITS - exponent_bits)
	{
	  /* Bigger than one littlenum.  */
	  num_bits -= (LITTLENUM_NUMBER_OF_BITS - 1) - exponent_bits;
	  *lp++ = word1;
	  if (num_bits + exponent_bits + 1
	      > precision * LITTLENUM_NUMBER_OF_BITS)
	    {
	      /* Exponent overflow.  */
	      make_invalid_floating_point_number (words);
	      return return_value;
	    }
#ifdef TC_M68K
	  if (precision == X_PRECISION && exponent_bits == 15)
	    *lp++ = 0;
#endif
	  while (num_bits >= LITTLENUM_NUMBER_OF_BITS)
	    {
	      num_bits -= LITTLENUM_NUMBER_OF_BITS;
	      *lp++ = 0;
	    }
	  if (num_bits)
	    *lp++ = next_bits (LITTLENUM_NUMBER_OF_BITS - (num_bits));
	}
      else
	{
	  if (precision == X_PRECISION && exponent_bits == 15)
	    {
	      *lp++ = word1;
#ifdef TC_M68K
	      *lp++ = 0;
#endif
	      *lp++ = next_bits (LITTLENUM_NUMBER_OF_BITS - num_bits);
	    }
	  else
	    {
	      word1 |= next_bits ((LITTLENUM_NUMBER_OF_BITS - 1)
				  - (exponent_bits + num_bits));
	      *lp++ = word1;
	    }
	}
      while (lp < words_end)
	*lp++ = next_bits (LITTLENUM_NUMBER_OF_BITS);

      /* Round the mantissa up, but don't change the number.  */
      if (next_bits (1))
	{
	  --lp;
	  if (prec_bits >= LITTLENUM_NUMBER_OF_BITS)
	    {
	      int n = 0;
	      int tmp_bits;

	      n = 0;
	      tmp_bits = prec_bits;
	      while (tmp_bits > LITTLENUM_NUMBER_OF_BITS)
		{
		  if (lp[n] != (LITTLENUM_TYPE) - 1)
		    break;
		  --n;
		  tmp_bits -= LITTLENUM_NUMBER_OF_BITS;
		}
	      if (tmp_bits > LITTLENUM_NUMBER_OF_BITS
		  || (lp[n] & mask[tmp_bits]) != mask[tmp_bits]
		  || (prec_bits != (precision * LITTLENUM_NUMBER_OF_BITS
				    - exponent_bits - 1)
#ifdef TC_I386
		      /* An extended precision float with only the integer
			 bit set would be invalid.  That must be converted
			 to the smallest normalized number.  */
		      && !(precision == X_PRECISION
			   && prec_bits == (precision * LITTLENUM_NUMBER_OF_BITS
					    - exponent_bits - 2))
#endif
		      ))
		{
		  unsigned long carry;

		  for (carry = 1; carry && (lp >= words); lp--)
		    {
		      carry = *lp + carry;
		      *lp = carry;
		      carry >>= LITTLENUM_NUMBER_OF_BITS;
		    }
		}
	      else
		{
		  /* This is an overflow of the denormal numbers.  We
                     need to forget what we have produced, and instead
                     generate the smallest normalized number.  */
		  lp = words;
		  word1 = ((generic_floating_point_number.sign == '+')
			   ? 0
			   : (1 << (LITTLENUM_NUMBER_OF_BITS - 1)));
		  word1 |= (1
			    << ((LITTLENUM_NUMBER_OF_BITS - 1)
				- exponent_bits));
		  *lp++ = word1;
#ifdef TC_I386
		  /* Set the integer bit in the extended precision format.
		     This cannot happen on the m68k where the mantissa
		     just overflows into the integer bit above.  */
		  if (precision == X_PRECISION)
		    *lp++ = 1 << (LITTLENUM_NUMBER_OF_BITS - 1);
#endif
		  while (lp < words_end)
		    *lp++ = 0;
		}
	    }
	  else
	    *lp += 1;
	}

      return return_value;
    }
  else if ((unsigned long) exponent_4 > mask[exponent_bits]
	   || (! TC_LARGEST_EXPONENT_IS_NORMAL (precision)
	       && (unsigned long) exponent_4 == mask[exponent_bits]))
    {
      /* Exponent overflow.  Lose immediately.  */

      /* We leave return_value alone: admit we read the
	 number, but return a floating exception
	 because we can't encode the number.  */
      make_invalid_floating_point_number (words);
      return return_value;
    }
  else
    {
      word1 |= (exponent_4 << ((LITTLENUM_NUMBER_OF_BITS - 1) - exponent_bits))
	| next_bits ((LITTLENUM_NUMBER_OF_BITS - 1) - exponent_bits);
    }

  *lp++ = word1;

  /* X_PRECISION is special: on the 68k, it has 16 bits of zero in the
     middle.  Either way, it is then followed by a 1 bit.  */
  if (exponent_bits == 15 && precision == X_PRECISION)
    {
#ifdef TC_M68K
      *lp++ = 0;
#endif
      *lp++ = (1 << (LITTLENUM_NUMBER_OF_BITS - 1)
	       | next_bits (LITTLENUM_NUMBER_OF_BITS - 1));
    }

  /* The rest of the words are just mantissa bits.  */
  while (lp < words_end)
    *lp++ = next_bits (LITTLENUM_NUMBER_OF_BITS);

  if (next_bits (1))
    {
      unsigned long carry;
      /* Since the NEXT bit is a 1, round UP the mantissa.
	 The cunning design of these hidden-1 floats permits
	 us to let the mantissa overflow into the exponent, and
	 it 'does the right thing'. However, we lose if the
	 highest-order bit of the lowest-order word flips.
	 Is that clear?  */

      /* #if (sizeof(carry)) < ((sizeof(bits[0]) * BITS_PER_CHAR) + 2)
	 Please allow at least 1 more bit in carry than is in a LITTLENUM.
	 We need that extra bit to hold a carry during a LITTLENUM carry
	 propagation. Another extra bit (kept 0) will assure us that we
	 don't get a sticky sign bit after shifting right, and that
	 permits us to propagate the carry without any masking of bits.
	 #endif */
      for (carry = 1, lp--; carry; lp--)
	{
	  carry = *lp + carry;
	  *lp = carry;
	  carry >>= LITTLENUM_NUMBER_OF_BITS;
	  if (lp == words)
	    break;
	}
      if (precision == X_PRECISION && exponent_bits == 15)
	{
	  /* Extended precision numbers have an explicit integer bit
	     that we may have to restore.  */
	  if (lp == words)
	    {
#ifdef TC_M68K
	      /* On the m68k there is a gap of 16 bits.  We must
		 explicitly propagate the carry into the exponent.  */
	      words[0] += words[1];
	      words[1] = 0;
	      lp++;
#endif
	      /* Put back the integer bit.  */
	      lp[1] |= 1 << (LITTLENUM_NUMBER_OF_BITS - 1);
	    }
	}
      if ((word1 ^ *words) & (1 << (LITTLENUM_NUMBER_OF_BITS - 1)))
	{
	  /* We leave return_value alone: admit we read the number,
	     but return a floating exception because we can't encode
	     the number.  */
	  *words &= ~(1 << (LITTLENUM_NUMBER_OF_BITS - 1));
	}
    }
  return return_value;
}