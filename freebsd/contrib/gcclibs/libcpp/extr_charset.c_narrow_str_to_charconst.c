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
typedef  size_t cppchar_t ;
struct TYPE_3__ {int len; size_t* text; } ;
typedef  TYPE_1__ cpp_string ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 size_t BITS_PER_CPPCHAR_T ; 
 int /*<<< orphan*/  CPP_DL_WARNING ; 
 size_t CPP_OPTION (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  char_precision ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  int_precision ; 
 int /*<<< orphan*/  unsigned_char ; 
 int /*<<< orphan*/  warn_multichar ; 
 size_t width_to_mask (size_t) ; 

__attribute__((used)) static cppchar_t
narrow_str_to_charconst (cpp_reader *pfile, cpp_string str,
			 unsigned int *pchars_seen, int *unsignedp)
{
  size_t width = CPP_OPTION (pfile, char_precision);
  size_t max_chars = CPP_OPTION (pfile, int_precision) / width;
  size_t mask = width_to_mask (width);
  size_t i;
  cppchar_t result, c;
  bool unsigned_p;

  /* The value of a multi-character character constant, or a
     single-character character constant whose representation in the
     execution character set is more than one byte long, is
     implementation defined.  This implementation defines it to be the
     number formed by interpreting the byte sequence in memory as a
     big-endian binary number.  If overflow occurs, the high bytes are
     lost, and a warning is issued.

     We don't want to process the NUL terminator handed back by
     cpp_interpret_string.  */
  result = 0;
  for (i = 0; i < str.len - 1; i++)
    {
      c = str.text[i] & mask;
      if (width < BITS_PER_CPPCHAR_T)
	result = (result << width) | c;
      else
	result = c;
    }

  if (i > max_chars)
    {
      i = max_chars;
      cpp_error (pfile, CPP_DL_WARNING,
		 "character constant too long for its type");
    }
  else if (i > 1 && CPP_OPTION (pfile, warn_multichar))
    cpp_error (pfile, CPP_DL_WARNING, "multi-character character constant");

  /* Multichar constants are of type int and therefore signed.  */
  if (i > 1)
    unsigned_p = 0;
  else
    unsigned_p = CPP_OPTION (pfile, unsigned_char);

  /* Truncate the constant to its natural width, and simultaneously
     sign- or zero-extend to the full width of cppchar_t.
     For single-character constants, the value is WIDTH bits wide.
     For multi-character constants, the value is INT_PRECISION bits wide.  */
  if (i > 1)
    width = CPP_OPTION (pfile, int_precision);
  if (width < BITS_PER_CPPCHAR_T)
    {
      mask = ((cppchar_t) 1 << width) - 1;
      if (unsigned_p || !(result & (1 << (width - 1))))
	result &= mask;
      else
	result |= ~mask;
    }
  *pchars_seen = i;
  *unsignedp = unsigned_p;
  return result;
}