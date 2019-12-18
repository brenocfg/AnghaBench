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

__attribute__((used)) static long long
extract_bit_field (char *bundle, int from, int len)
{
  long long result = 0LL;
  int to = from + len;
  int from_byte = from / 8;
  int to_byte = to / 8;
  unsigned char *b = (unsigned char *) bundle;
  unsigned char c;
  int lshift;
  int i;

  c = b[from_byte];
  if (from_byte == to_byte)
    c = ((unsigned char) (c << (8 - to % 8))) >> (8 - to % 8);
  result = c >> (from % 8);
  lshift = 8 - (from % 8);

  for (i = from_byte+1; i < to_byte; i++)
    {
      result |= ((long long) b[i]) << lshift;
      lshift += 8;
    }

  if (from_byte < to_byte && (to % 8 != 0))
    {
      c = b[to_byte];
      c = ((unsigned char) (c << (8 - to % 8))) >> (8 - to % 8);
      result |= ((long long) c) << lshift;
    }

  return result;
}