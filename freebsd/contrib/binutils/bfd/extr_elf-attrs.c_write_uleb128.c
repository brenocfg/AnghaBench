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
typedef  int bfd_byte ;

/* Variables and functions */

__attribute__((used)) static bfd_byte *
write_uleb128 (bfd_byte *p, unsigned int val)
{
  bfd_byte c;
  do
    {
      c = val & 0x7f;
      val >>= 7;
      if (val)
	c |= 0x80;
      *(p++) = c;
    }
  while (val);
  return p;
}