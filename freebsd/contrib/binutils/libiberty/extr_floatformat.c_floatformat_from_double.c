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
struct floatformat {int totalsize; unsigned int sign_start; unsigned int exp_start; unsigned int exp_len; unsigned long exp_nan; unsigned int man_start; int exp_bias; int man_len; scalar_t__ intbit; int /*<<< orphan*/  byteorder; } ;

/* Variables and functions */
 int FLOATFORMAT_CHAR_BIT ; 
 scalar_t__ floatformat_intbit_no ; 
 double frexp (double,int*) ; 
 double ldexp (double,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_field (unsigned char*,int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned long) ; 

void
floatformat_from_double (const struct floatformat *fmt,
                         const double *from, void *to)
{
  double dfrom;
  int exponent;
  double mant;
  unsigned int mant_bits, mant_off;
  int mant_bits_left;
  unsigned char *uto = (unsigned char *) to;

  dfrom = *from;
  memset (uto, 0, fmt->totalsize / FLOATFORMAT_CHAR_BIT);

  /* If negative, set the sign bit.  */
  if (dfrom < 0)
    {
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->sign_start, 1, 1);
      dfrom = -dfrom;
    }

  if (dfrom == 0)
    {
      /* 0.0.  */
      return;
    }

  if (dfrom != dfrom)
    {
      /* NaN.  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
		 fmt->exp_len, fmt->exp_nan);
      /* Be sure it's not infinity, but NaN value is irrelevant.  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->man_start,
		 32, 1);
      return;
    }

  if (dfrom + dfrom == dfrom)
    {
      /* This can only happen for an infinite value (or zero, which we
	 already handled above).  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
		 fmt->exp_len, fmt->exp_nan);
      return;
    }

  mant = frexp (dfrom, &exponent);
  if (exponent + fmt->exp_bias - 1 > 0)
    put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
	       fmt->exp_len, exponent + fmt->exp_bias - 1);
  else
    {
      /* Handle a denormalized number.  FIXME: What should we do for
	 non-IEEE formats?  */
      put_field (uto, fmt->byteorder, fmt->totalsize, fmt->exp_start,
		 fmt->exp_len, 0);
      mant = ldexp (mant, exponent + fmt->exp_bias - 1);
    }

  mant_bits_left = fmt->man_len;
  mant_off = fmt->man_start;
  while (mant_bits_left > 0)
    {
      unsigned long mant_long;
      mant_bits = mant_bits_left < 32 ? mant_bits_left : 32;

      mant *= 4294967296.0;
      mant_long = (unsigned long)mant;
      mant -= mant_long;

      /* If the integer bit is implicit, and we are not creating a
	 denormalized number, then we need to discard it.  */
      if ((unsigned int) mant_bits_left == fmt->man_len
	  && fmt->intbit == floatformat_intbit_no
	  && exponent + fmt->exp_bias - 1 > 0)
	{
	  mant_long &= 0x7fffffff;
	  mant_bits -= 1;
	}
      else if (mant_bits < 32)
	{
	  /* The bits we want are in the most significant MANT_BITS bits of
	     mant_long.  Move them to the least significant.  */
	  mant_long >>= 32 - mant_bits;
	}

      put_field (uto, fmt->byteorder, fmt->totalsize,
		 mant_off, mant_bits, mant_long);
      mant_off += mant_bits;
      mant_bits_left -= mant_bits;
    }
}