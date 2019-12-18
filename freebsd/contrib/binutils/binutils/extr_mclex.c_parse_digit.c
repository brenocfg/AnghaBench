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
typedef  char unichar ;
typedef  int rc_uint_type ;

/* Variables and functions */
 int* input_stream_pos ; 

__attribute__((used)) static rc_uint_type
parse_digit (unichar ch)
{
  rc_uint_type base = 10, v = 0, c;

  if (ch == '0')
    {
      base = 8;
      switch (input_stream_pos[0])
	{
	case 'x': case 'X': base = 16; input_stream_pos++; break;
	case 'o': case 'O': base = 8; input_stream_pos++; break;
	case 'b': case 'B': base = 2; input_stream_pos++; break;
	}
    }
  else
    v = (rc_uint_type) (ch - '0');

  while ((ch = input_stream_pos[0]) != 0)
    {
      if (ch >= 'A' && ch <= 'F')
	c = (rc_uint_type) (ch - 'A') + 10;
      else if (ch >= 'a' && ch <= 'f')
	c = (rc_uint_type) (ch - 'a') + 10;
      else if (ch >= '0' && ch <= '9')
	c = (rc_uint_type) (ch - '0');
      else
	break;
      v *= base;
      v += c;
      ++input_stream_pos;
    }
  if (input_stream_pos[0] == 'U' || input_stream_pos[0] == 'u')
    input_stream_pos++;
  if (input_stream_pos[0] == 'L' || input_stream_pos[0] == 'l')
    input_stream_pos++;
  if (input_stream_pos[0] == 'L' || input_stream_pos[0] == 'l')
    input_stream_pos++;
  return v;
}