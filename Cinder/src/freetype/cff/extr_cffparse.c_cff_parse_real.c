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
typedef  int FT_ULong ;
typedef  int FT_UInt ;
typedef  int FT_Long ;
typedef  int FT_Int ;
typedef  int FT_Fixed ;
typedef  int FT_Byte ;

/* Variables and functions */
 int FT_DivFix (int,int) ; 
 int FT_MIN (int,int) ; 
 int /*<<< orphan*/  FT_TRACE4 (char*) ; 
 int* power_tens ; 

__attribute__((used)) static FT_Fixed
  cff_parse_real( FT_Byte*  start,
                  FT_Byte*  limit,
                  FT_Long   power_ten,
                  FT_Long*  scaling )
  {
    FT_Byte*  p = start;
    FT_Int    nib;
    FT_UInt   phase;

    FT_Long   result, number, exponent;
    FT_Int    sign = 0, exponent_sign = 0, have_overflow = 0;
    FT_Long   exponent_add, integer_length, fraction_length;


    if ( scaling )
      *scaling = 0;

    result = 0;

    number   = 0;
    exponent = 0;

    exponent_add    = 0;
    integer_length  = 0;
    fraction_length = 0;

    /* First of all, read the integer part. */
    phase = 4;

    for (;;)
    {
      /* If we entered this iteration with phase == 4, we need to */
      /* read a new byte.  This also skips past the initial 0x1E. */
      if ( phase )
      {
        p++;

        /* Make sure we don't read past the end. */
        if ( p >= limit )
          goto Bad;
      }

      /* Get the nibble. */
      nib   = (FT_Int)( p[0] >> phase ) & 0xF;
      phase = 4 - phase;

      if ( nib == 0xE )
        sign = 1;
      else if ( nib > 9 )
        break;
      else
      {
        /* Increase exponent if we can't add the digit. */
        if ( number >= 0xCCCCCCCL )
          exponent_add++;
        /* Skip leading zeros. */
        else if ( nib || number )
        {
          integer_length++;
          number = number * 10 + nib;
        }
      }
    }

    /* Read fraction part, if any. */
    if ( nib == 0xA )
      for (;;)
      {
        /* If we entered this iteration with phase == 4, we need */
        /* to read a new byte.                                   */
        if ( phase )
        {
          p++;

          /* Make sure we don't read past the end. */
          if ( p >= limit )
            goto Bad;
        }

        /* Get the nibble. */
        nib   = ( p[0] >> phase ) & 0xF;
        phase = 4 - phase;
        if ( nib >= 10 )
          break;

        /* Skip leading zeros if possible. */
        if ( !nib && !number )
          exponent_add--;
        /* Only add digit if we don't overflow. */
        else if ( number < 0xCCCCCCCL && fraction_length < 9 )
        {
          fraction_length++;
          number = number * 10 + nib;
        }
      }

    /* Read exponent, if any. */
    if ( nib == 12 )
    {
      exponent_sign = 1;
      nib           = 11;
    }

    if ( nib == 11 )
    {
      for (;;)
      {
        /* If we entered this iteration with phase == 4, */
        /* we need to read a new byte.                   */
        if ( phase )
        {
          p++;

          /* Make sure we don't read past the end. */
          if ( p >= limit )
            goto Bad;
        }

        /* Get the nibble. */
        nib   = ( p[0] >> phase ) & 0xF;
        phase = 4 - phase;
        if ( nib >= 10 )
          break;

        /* Arbitrarily limit exponent. */
        if ( exponent > 1000 )
          have_overflow = 1;
        else
          exponent = exponent * 10 + nib;
      }

      if ( exponent_sign )
        exponent = -exponent;
    }

    if ( !number )
      goto Exit;

    if ( have_overflow )
    {
      if ( exponent_sign )
        goto Underflow;
      else
        goto Overflow;
    }

    /* We don't check `power_ten' and `exponent_add'. */
    exponent += power_ten + exponent_add;

    if ( scaling )
    {
      /* Only use `fraction_length'. */
      fraction_length += integer_length;
      exponent        += integer_length;

      if ( fraction_length <= 5 )
      {
        if ( number > 0x7FFFL )
        {
          result   = FT_DivFix( number, 10 );
          *scaling = exponent - fraction_length + 1;
        }
        else
        {
          if ( exponent > 0 )
          {
            FT_Long  new_fraction_length, shift;


            /* Make `scaling' as small as possible. */
            new_fraction_length = FT_MIN( exponent, 5 );
            shift               = new_fraction_length - fraction_length;

            if ( shift > 0 )
            {
              exponent -= new_fraction_length;
              number   *= power_tens[shift];
              if ( number > 0x7FFFL )
              {
                number   /= 10;
                exponent += 1;
              }
            }
            else
              exponent -= fraction_length;
          }
          else
            exponent -= fraction_length;

          result   = (FT_Long)( (FT_ULong)number << 16 );
          *scaling = exponent;
        }
      }
      else
      {
        if ( ( number / power_tens[fraction_length - 5] ) > 0x7FFFL )
        {
          result   = FT_DivFix( number, power_tens[fraction_length - 4] );
          *scaling = exponent - 4;
        }
        else
        {
          result   = FT_DivFix( number, power_tens[fraction_length - 5] );
          *scaling = exponent - 5;
        }
      }
    }
    else
    {
      integer_length  += exponent;
      fraction_length -= exponent;

      if ( integer_length > 5 )
        goto Overflow;
      if ( integer_length < -5 )
        goto Underflow;

      /* Remove non-significant digits. */
      if ( integer_length < 0 )
      {
        number          /= power_tens[-integer_length];
        fraction_length += integer_length;
      }

      /* this can only happen if exponent was non-zero */
      if ( fraction_length == 10 )
      {
        number          /= 10;
        fraction_length -= 1;
      }

      /* Convert into 16.16 format. */
      if ( fraction_length > 0 )
      {
        if ( ( number / power_tens[fraction_length] ) > 0x7FFFL )
          goto Exit;

        result = FT_DivFix( number, power_tens[fraction_length] );
      }
      else
      {
        number *= power_tens[-fraction_length];

        if ( number > 0x7FFFL )
          goto Overflow;

        result = (FT_Long)( (FT_ULong)number << 16 );
      }
    }

  Exit:
    if ( sign )
      result = -result;

    return result;

  Overflow:
    result = 0x7FFFFFFFL;
    FT_TRACE4(( "!!!OVERFLOW:!!!" ));
    goto Exit;

  Underflow:
    result = 0;
    FT_TRACE4(( "!!!UNDERFLOW:!!!" ));
    goto Exit;

  Bad:
    result = 0;
    FT_TRACE4(( "!!!END OF DATA:!!!" ));
    goto Exit;
  }