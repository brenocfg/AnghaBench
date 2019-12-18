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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 scalar_t__ hex_p (char) ; 
 int hex_value (char) ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ target_big_endian ; 

__attribute__((used)) static int
hex_float (int float_type, char *bytes)
{
  int length;
  int i;

  switch (float_type)
    {
    case 'f':
    case 'F':
    case 's':
    case 'S':
      length = 4;
      break;

    case 'd':
    case 'D':
    case 'r':
    case 'R':
      length = 8;
      break;

    case 'x':
    case 'X':
      length = 12;
      break;

    case 'p':
    case 'P':
      length = 12;
      break;

    default:
      as_bad (_("unknown floating type type '%c'"), float_type);
      return -1;
    }

  /* It would be nice if we could go through expression to parse the
     hex constant, but if we get a bignum it's a pain to sort it into
     the buffer correctly.  */
  i = 0;
  while (hex_p (*input_line_pointer) || *input_line_pointer == '_')
    {
      int d;

      /* The MRI assembler accepts arbitrary underscores strewn about
	 through the hex constant, so we ignore them as well.  */
      if (*input_line_pointer == '_')
	{
	  ++input_line_pointer;
	  continue;
	}

      if (i >= length)
	{
	  as_warn (_("floating point constant too large"));
	  return -1;
	}
      d = hex_value (*input_line_pointer) << 4;
      ++input_line_pointer;
      while (*input_line_pointer == '_')
	++input_line_pointer;
      if (hex_p (*input_line_pointer))
	{
	  d += hex_value (*input_line_pointer);
	  ++input_line_pointer;
	}
      if (target_big_endian)
	bytes[i] = d;
      else
	bytes[length - i - 1] = d;
      ++i;
    }

  if (i < length)
    {
      if (target_big_endian)
	memset (bytes + i, 0, length - i);
      else
	memset (bytes, 0, length - i);
    }

  return length;
}