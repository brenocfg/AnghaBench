#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char uchar ;
struct TYPE_5__ {char* text; int len; } ;
struct TYPE_6__ {TYPE_1__ str; } ;
struct TYPE_7__ {TYPE_2__ val; } ;
typedef  TYPE_3__ cpp_token ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 int /*<<< orphan*/  CPP_DL_PEDWARN ; 
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 unsigned int CPP_N_BINARY ; 
 unsigned int CPP_N_DECIMAL ; 
 unsigned int CPP_N_DFLOAT ; 
 unsigned int CPP_N_FLOATING ; 
 unsigned int CPP_N_HEX ; 
 unsigned int CPP_N_IMAGINARY ; 
 unsigned int CPP_N_INTEGER ; 
 unsigned int CPP_N_INVALID ; 
 unsigned int CPP_N_LARGE ; 
 unsigned int CPP_N_MEDIUM ; 
 unsigned int CPP_N_OCTAL ; 
 unsigned int CPP_N_SMALL ; 
 unsigned int CPP_N_UNSIGNED ; 
 unsigned int CPP_N_WIDTH ; 
 scalar_t__ CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CPP_PEDANTIC (int /*<<< orphan*/ *) ; 
 scalar_t__ CPP_WTRADITIONAL (int /*<<< orphan*/ *) ; 
 scalar_t__ ISDIGIT (char const) ; 
 scalar_t__ ISXDIGIT (char const) ; 
 int /*<<< orphan*/  SYNTAX_ERROR (char*) ; 
 int /*<<< orphan*/  SYNTAX_ERROR2 (char*,unsigned int) ; 
 int /*<<< orphan*/  c99 ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cpp_sys_macro_p (int /*<<< orphan*/ *) ; 
 unsigned int hex_value (unsigned int) ; 
 unsigned int interpret_float_suffix (char const*,int) ; 
 unsigned int interpret_int_suffix (char const*,int) ; 
 int /*<<< orphan*/  warn_long_long ; 

unsigned int
cpp_classify_number (cpp_reader *pfile, const cpp_token *token)
{
  const uchar *str = token->val.str.text;
  const uchar *limit;
  unsigned int max_digit, result, radix;
  enum {NOT_FLOAT = 0, AFTER_POINT, AFTER_EXPON} float_flag;

  /* If the lexer has done its job, length one can only be a single
     digit.  Fast-path this very common case.  */
  if (token->val.str.len == 1)
    return CPP_N_INTEGER | CPP_N_SMALL | CPP_N_DECIMAL;

  limit = str + token->val.str.len;
  float_flag = NOT_FLOAT;
  max_digit = 0;
  radix = 10;

  /* First, interpret the radix.  */
  if (*str == '0')
    {
      radix = 8;
      str++;

      /* Require at least one hex digit to classify it as hex.  */
      if ((*str == 'x' || *str == 'X')
	  && (str[1] == '.' || ISXDIGIT (str[1])))
	{
	  radix = 16;
	  str++;
	}
      else if ((*str == 'b' || *str == 'B') && (str[1] == '0' || str[1] == '1'))
	{
	  radix = 2;
	  str++;
	}
    }

  /* Now scan for a well-formed integer or float.  */
  for (;;)
    {
      unsigned int c = *str++;

      if (ISDIGIT (c) || (ISXDIGIT (c) && radix == 16))
	{
	  c = hex_value (c);
	  if (c > max_digit)
	    max_digit = c;
	}
      else if (c == '.')
	{
	  if (float_flag == NOT_FLOAT)
	    float_flag = AFTER_POINT;
	  else
	    SYNTAX_ERROR ("too many decimal points in number");
	}
      else if ((radix <= 10 && (c == 'e' || c == 'E'))
	       || (radix == 16 && (c == 'p' || c == 'P')))
	{
	  float_flag = AFTER_EXPON;
	  break;
	}
      else
	{
	  /* Start of suffix.  */
	  str--;
	  break;
	}
    }

  if (float_flag != NOT_FLOAT && radix == 8)
    radix = 10;

  if (max_digit >= radix)
    {
      if (radix == 2)
	SYNTAX_ERROR2 ("invalid digit \"%c\" in binary constant", '0' + max_digit);
      else
	SYNTAX_ERROR2 ("invalid digit \"%c\" in octal constant", '0' + max_digit);
    }

  if (float_flag != NOT_FLOAT)
    {
      if (radix == 2)
	{
	  cpp_error (pfile, CPP_DL_ERROR,
		     "invalid prefix \"0b\" for floating constant");
	  return CPP_N_INVALID;
	}

      if (radix == 16 && CPP_PEDANTIC (pfile) && !CPP_OPTION (pfile, c99))
	cpp_error (pfile, CPP_DL_PEDWARN,
		   "use of C99 hexadecimal floating constant");

      if (float_flag == AFTER_EXPON)
	{
	  if (*str == '+' || *str == '-')
	    str++;

	  /* Exponent is decimal, even if string is a hex float.  */
	  if (!ISDIGIT (*str))
	    SYNTAX_ERROR ("exponent has no digits");

	  do
	    str++;
	  while (ISDIGIT (*str));
	}
      else if (radix == 16)
	SYNTAX_ERROR ("hexadecimal floating constants require an exponent");

      result = interpret_float_suffix (str, limit - str);
      if (result == 0)
	{
	  cpp_error (pfile, CPP_DL_ERROR,
		     "invalid suffix \"%.*s\" on floating constant",
		     (int) (limit - str), str);
	  return CPP_N_INVALID;
	}

      /* Traditional C didn't accept any floating suffixes.  */
      if (limit != str
	  && CPP_WTRADITIONAL (pfile)
	  && ! cpp_sys_macro_p (pfile))
	cpp_error (pfile, CPP_DL_WARNING,
		   "traditional C rejects the \"%.*s\" suffix",
		   (int) (limit - str), str);

      /* A suffix for double is a GCC extension via decimal float support.
	 If the suffix also specifies an imaginary value we'll catch that
	 later.  */
      if ((result == CPP_N_MEDIUM) && CPP_PEDANTIC (pfile))
	cpp_error (pfile, CPP_DL_PEDWARN,
		   "suffix for double constant is a GCC extension");

      /* Radix must be 10 for decimal floats.  */
      if ((result & CPP_N_DFLOAT) && radix != 10)
        {
          cpp_error (pfile, CPP_DL_ERROR,
                     "invalid suffix \"%.*s\" with hexadecimal floating constant",
                     (int) (limit - str), str);
          return CPP_N_INVALID;
        }

      result |= CPP_N_FLOATING;
    }
  else
    {
      result = interpret_int_suffix (str, limit - str);
      if (result == 0)
	{
	  cpp_error (pfile, CPP_DL_ERROR,
		     "invalid suffix \"%.*s\" on integer constant",
		     (int) (limit - str), str);
	  return CPP_N_INVALID;
	}

      /* Traditional C only accepted the 'L' suffix.
         Suppress warning about 'LL' with -Wno-long-long.  */
      if (CPP_WTRADITIONAL (pfile) && ! cpp_sys_macro_p (pfile))
	{
	  int u_or_i = (result & (CPP_N_UNSIGNED|CPP_N_IMAGINARY));
	  int large = (result & CPP_N_WIDTH) == CPP_N_LARGE;

	  if (u_or_i || (large && CPP_OPTION (pfile, warn_long_long)))
	    cpp_error (pfile, CPP_DL_WARNING,
		       "traditional C rejects the \"%.*s\" suffix",
		       (int) (limit - str), str);
	}

      if ((result & CPP_N_WIDTH) == CPP_N_LARGE
	  && ! CPP_OPTION (pfile, c99)
	  && CPP_OPTION (pfile, warn_long_long))
	cpp_error (pfile, CPP_DL_PEDWARN,
		   "use of C99 long long integer constant");

      result |= CPP_N_INTEGER;
    }

  if ((result & CPP_N_IMAGINARY) && CPP_PEDANTIC (pfile))
    cpp_error (pfile, CPP_DL_PEDWARN,
	       "imaginary constants are a GCC extension");
  if (radix == 2 && CPP_PEDANTIC (pfile))
    cpp_error (pfile, CPP_DL_PEDWARN,
	       "binary constants are a GCC extension");

  if (radix == 10)
    result |= CPP_N_DECIMAL;
  else if (radix == 16)
    result |= CPP_N_HEX;
  else if (radix == 2)
    result |= CPP_N_BINARY;
  else
    result |= CPP_N_OCTAL;

  return result;

 syntax_error:
  return CPP_N_INVALID;
}