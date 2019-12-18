#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {unsigned long* sig; scalar_t__ cl; int sign; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int HOST_BITS_PER_LONG ; 
 scalar_t__ ISDIGIT (char const) ; 
 int MAX_EXP ; 
 int /*<<< orphan*/  SET_REAL_EXP (TYPE_1__*,int) ; 
 int SIGNIFICAND_BITS ; 
 int _hex_bad ; 
 int /*<<< orphan*/  cmp_significand_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  do_add (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_multiply (TYPE_1__*,TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  get_inf (TYPE_1__*,int) ; 
 int /*<<< orphan*/  get_zero (TYPE_1__*,int) ; 
 int hex_value (char const) ; 
 int /*<<< orphan*/  normalize (TYPE_1__*) ; 
 int /*<<< orphan*/  real_digit (int) ; 
 scalar_t__ rvc_normal ; 
 scalar_t__ rvc_zero ; 
 TYPE_1__* ten_to_ptwo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  times_pten (TYPE_1__*,int) ; 

void
real_from_string (REAL_VALUE_TYPE *r, const char *str)
{
  int exp = 0;
  bool sign = false;

  get_zero (r, 0);

  if (*str == '-')
    {
      sign = true;
      str++;
    }
  else if (*str == '+')
    str++;

  if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
      /* Hexadecimal floating point.  */
      int pos = SIGNIFICAND_BITS - 4, d;

      str += 2;

      while (*str == '0')
	str++;
      while (1)
	{
	  d = hex_value (*str);
	  if (d == _hex_bad)
	    break;
	  if (pos >= 0)
	    {
	      r->sig[pos / HOST_BITS_PER_LONG]
		|= (unsigned long) d << (pos % HOST_BITS_PER_LONG);
	      pos -= 4;
	    }
	  else if (d)
	    /* Ensure correct rounding by setting last bit if there is
	       a subsequent nonzero digit.  */
	    r->sig[0] |= 1;
	  exp += 4;
	  str++;
	}
      if (*str == '.')
	{
	  str++;
	  if (pos == SIGNIFICAND_BITS - 4)
	    {
	      while (*str == '0')
		str++, exp -= 4;
	    }
	  while (1)
	    {
	      d = hex_value (*str);
	      if (d == _hex_bad)
		break;
	      if (pos >= 0)
		{
		  r->sig[pos / HOST_BITS_PER_LONG]
		    |= (unsigned long) d << (pos % HOST_BITS_PER_LONG);
		  pos -= 4;
		}
	      else if (d)
		/* Ensure correct rounding by setting last bit if there is
		   a subsequent nonzero digit.  */
		r->sig[0] |= 1;
	      str++;
	    }
	}

      /* If the mantissa is zero, ignore the exponent.  */
      if (!cmp_significand_0 (r))
	goto underflow;

      if (*str == 'p' || *str == 'P')
	{
	  bool exp_neg = false;

	  str++;
	  if (*str == '-')
	    {
	      exp_neg = true;
	      str++;
	    }
	  else if (*str == '+')
	    str++;

	  d = 0;
	  while (ISDIGIT (*str))
	    {
	      d *= 10;
	      d += *str - '0';
	      if (d > MAX_EXP)
		{
		  /* Overflowed the exponent.  */
		  if (exp_neg)
		    goto underflow;
		  else
		    goto overflow;
		}
	      str++;
	    }
	  if (exp_neg)
	    d = -d;

	  exp += d;
	}

      r->cl = rvc_normal;
      SET_REAL_EXP (r, exp);

      normalize (r);
    }
  else
    {
      /* Decimal floating point.  */
      const REAL_VALUE_TYPE *ten = ten_to_ptwo (0);
      int d;

      while (*str == '0')
	str++;
      while (ISDIGIT (*str))
	{
	  d = *str++ - '0';
	  do_multiply (r, r, ten);
	  if (d)
	    do_add (r, r, real_digit (d), 0);
	}
      if (*str == '.')
	{
	  str++;
	  if (r->cl == rvc_zero)
	    {
	      while (*str == '0')
		str++, exp--;
	    }
	  while (ISDIGIT (*str))
	    {
	      d = *str++ - '0';
	      do_multiply (r, r, ten);
	      if (d)
	        do_add (r, r, real_digit (d), 0);
	      exp--;
	    }
	}

      /* If the mantissa is zero, ignore the exponent.  */
      if (r->cl == rvc_zero)
	goto underflow;

      if (*str == 'e' || *str == 'E')
	{
	  bool exp_neg = false;

	  str++;
	  if (*str == '-')
	    {
	      exp_neg = true;
	      str++;
	    }
	  else if (*str == '+')
	    str++;

	  d = 0;
	  while (ISDIGIT (*str))
	    {
	      d *= 10;
	      d += *str - '0';
	      if (d > MAX_EXP)
		{
		  /* Overflowed the exponent.  */
		  if (exp_neg)
		    goto underflow;
		  else
		    goto overflow;
		}
	      str++;
	    }
	  if (exp_neg)
	    d = -d;
	  exp += d;
	}

      if (exp)
	times_pten (r, exp);
    }

  r->sign = sign;
  return;

 underflow:
  get_zero (r, sign);
  return;

 overflow:
  get_inf (r, sign);
  return;
}