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
typedef  int valueT ;

/* Variables and functions */

__attribute__((used)) static inline int
output_uleb128 (char *p, valueT value)
{
  char *orig = p;

  do
    {
      unsigned byte = (value & 0x7f);
      value >>= 7;
      if (value != 0)
	/* More bytes to follow.  */
	byte |= 0x80;

      *p++ = byte;
    }
  while (value != 0);

  return p - orig;
}