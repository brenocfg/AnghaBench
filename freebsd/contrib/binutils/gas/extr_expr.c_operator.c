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
typedef  int /*<<< orphan*/  operatorT ;

/* Variables and functions */
 int /*<<< orphan*/  O_bit_exclusive_or ; 
 int /*<<< orphan*/  O_bit_inclusive_or ; 
 int /*<<< orphan*/  O_eq ; 
 int /*<<< orphan*/  O_ge ; 
 int /*<<< orphan*/  O_illegal ; 
 int /*<<< orphan*/  O_le ; 
 int /*<<< orphan*/  O_left_shift ; 
 int /*<<< orphan*/  O_logical_and ; 
 int /*<<< orphan*/  O_logical_or ; 
 int /*<<< orphan*/  O_ne ; 
 int /*<<< orphan*/  O_right_shift ; 
 int /*<<< orphan*/  flag_m68k_mri ; 
 int* input_line_pointer ; 
 scalar_t__* is_end_of_line ; 
 int /*<<< orphan*/ * op_encoding ; 

__attribute__((used)) static inline operatorT
operator (int *num_chars)
{
  int c;
  operatorT ret;

  c = *input_line_pointer & 0xff;
  *num_chars = 1;

  if (is_end_of_line[c])
    return O_illegal;

  switch (c)
    {
    default:
      return op_encoding[c];

    case '+':
    case '-':
      return op_encoding[c];

    case '<':
      switch (input_line_pointer[1])
	{
	default:
	  return op_encoding[c];
	case '<':
	  ret = O_left_shift;
	  break;
	case '>':
	  ret = O_ne;
	  break;
	case '=':
	  ret = O_le;
	  break;
	}
      *num_chars = 2;
      return ret;

    case '=':
      if (input_line_pointer[1] != '=')
	return op_encoding[c];

      *num_chars = 2;
      return O_eq;

    case '>':
      switch (input_line_pointer[1])
	{
	default:
	  return op_encoding[c];
	case '>':
	  ret = O_right_shift;
	  break;
	case '=':
	  ret = O_ge;
	  break;
	}
      *num_chars = 2;
      return ret;

    case '!':
      switch (input_line_pointer[1])
	{
	case '!':
	  /* We accept !! as equivalent to ^ for MRI compatibility. */
	  *num_chars = 2;
	  return O_bit_exclusive_or;
	case '=':
	  /* We accept != as equivalent to <>.  */
	  *num_chars = 2;
	  return O_ne;
	default:
	  if (flag_m68k_mri)
	    return O_bit_inclusive_or;
	  return op_encoding[c];
	}

    case '|':
      if (input_line_pointer[1] != '|')
	return op_encoding[c];

      *num_chars = 2;
      return O_logical_or;

    case '&':
      if (input_line_pointer[1] != '&')
	return op_encoding[c];

      *num_chars = 2;
      return O_logical_and;
    }

  /* NOTREACHED  */
}