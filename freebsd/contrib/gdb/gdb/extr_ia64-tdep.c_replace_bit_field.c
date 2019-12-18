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

__attribute__((used)) static void
replace_bit_field (char *bundle, long long val, int from, int len)
{
  int to = from + len;
  int from_byte = from / 8;
  int to_byte = to / 8;
  unsigned char *b = (unsigned char *) bundle;
  unsigned char c;

  if (from_byte == to_byte)
    {
      unsigned char left, right;
      c = b[from_byte];
      left = (c >> (to % 8)) << (to % 8);
      right = ((unsigned char) (c << (8 - from % 8))) >> (8 - from % 8);
      c = (unsigned char) (val & 0xff);
      c = (unsigned char) (c << (from % 8 + 8 - to % 8)) >> (8 - to % 8);
      c |= right | left;
      b[from_byte] = c;
    }
  else
    {
      int i;
      c = b[from_byte];
      c = ((unsigned char) (c << (8 - from % 8))) >> (8 - from % 8);
      c = c | (val << (from % 8));
      b[from_byte] = c;
      val >>= 8 - from % 8;

      for (i = from_byte+1; i < to_byte; i++)
	{
	  c = val & 0xff;
	  val >>= 8;
	  b[i] = c;
	}

      if (to % 8 != 0)
	{
	  unsigned char cv = (unsigned char) val;
	  c = b[to_byte];
	  c = c >> (to % 8) << (to % 8);
	  c |= ((unsigned char) (cv << (8 - to % 8))) >> (8 - to % 8);
	  b[to_byte] = c;
	}
    }
}