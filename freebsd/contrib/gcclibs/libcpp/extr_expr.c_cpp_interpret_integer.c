#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uchar ;
struct TYPE_15__ {unsigned int* text; int len; } ;
struct TYPE_16__ {TYPE_1__ str; } ;
struct TYPE_18__ {TYPE_2__ val; } ;
typedef  TYPE_4__ cpp_token ;
struct TYPE_17__ {scalar_t__ in_directive; } ;
struct TYPE_19__ {TYPE_3__ state; } ;
typedef  TYPE_5__ cpp_reader ;
typedef  size_t cpp_num_part ;
struct TYPE_20__ {unsigned int low; int unsignedp; int overflow; scalar_t__ high; } ;
typedef  TYPE_6__ cpp_num ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_PEDWARN ; 
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 unsigned int CPP_N_BINARY ; 
 unsigned int CPP_N_HEX ; 
 unsigned int CPP_N_OCTAL ; 
 unsigned int CPP_N_RADIX ; 
 unsigned int CPP_N_UNSIGNED ; 
 size_t CPP_OPTION (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISDIGIT (unsigned int) ; 
 scalar_t__ ISXDIGIT (unsigned int) ; 
 size_t PART_PRECISION ; 
 TYPE_6__ append_digit (TYPE_6__,unsigned int,unsigned int,size_t) ; 
 int /*<<< orphan*/  cpp_error (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 unsigned int hex_value (unsigned int) ; 
 int /*<<< orphan*/  num_positive (TYPE_6__,size_t) ; 
 size_t precision ; 
 int /*<<< orphan*/  traditional ; 

cpp_num
cpp_interpret_integer (cpp_reader *pfile, const cpp_token *token,
		       unsigned int type)
{
  const uchar *p, *end;
  cpp_num result;

  result.low = 0;
  result.high = 0;
  result.unsignedp = !!(type & CPP_N_UNSIGNED);
  result.overflow = false;

  p = token->val.str.text;
  end = p + token->val.str.len;

  /* Common case of a single digit.  */
  if (token->val.str.len == 1)
    result.low = p[0] - '0';
  else
    {
      cpp_num_part max;
      size_t precision = CPP_OPTION (pfile, precision);
      unsigned int base = 10, c = 0;
      bool overflow = false;

      if ((type & CPP_N_RADIX) == CPP_N_OCTAL)
	{
	  base = 8;
	  p++;
	}
      else if ((type & CPP_N_RADIX) == CPP_N_HEX)
	{
	  base = 16;
	  p += 2;
	}
      else if ((type & CPP_N_RADIX) == CPP_N_BINARY)
	{
	  base = 2;
	  p += 2;
	}

      /* We can add a digit to numbers strictly less than this without
	 needing the precision and slowness of double integers.  */
      max = ~(cpp_num_part) 0;
      if (precision < PART_PRECISION)
	max >>= PART_PRECISION - precision;
      max = (max - base + 1) / base + 1;

      for (; p < end; p++)
	{
	  c = *p;

	  if (ISDIGIT (c) || (base == 16 && ISXDIGIT (c)))
	    c = hex_value (c);
	  else
	    break;

	  /* Strict inequality for when max is set to zero.  */
	  if (result.low < max)
	    result.low = result.low * base + c;
	  else
	    {
	      result = append_digit (result, c, base, precision);
	      overflow |= result.overflow;
	      max = 0;
	    }
	}

      if (overflow)
	cpp_error (pfile, CPP_DL_PEDWARN,
		   "integer constant is too large for its type");
      /* If too big to be signed, consider it unsigned.  Only warn for
	 decimal numbers.  Traditional numbers were always signed (but
	 we still honor an explicit U suffix); but we only have
	 traditional semantics in directives.  */
      else if (!result.unsignedp
	       && !(CPP_OPTION (pfile, traditional)
		    && pfile->state.in_directive)
	       && !num_positive (result, precision))
	{
	  if (base == 10)
	    cpp_error (pfile, CPP_DL_WARNING,
		       "integer constant is so large that it is unsigned");
	  result.unsignedp = true;
	}
    }

  return result;
}