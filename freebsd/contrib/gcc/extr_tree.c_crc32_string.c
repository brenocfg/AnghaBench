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

unsigned
crc32_string (unsigned chksum, const char *string)
{
  do
    {
      unsigned value = *string << 24;
      unsigned ix;

      for (ix = 8; ix--; value <<= 1)
  	{
  	  unsigned feedback;

  	  feedback = (value ^ chksum) & 0x80000000 ? 0x04c11db7 : 0;
 	  chksum <<= 1;
 	  chksum ^= feedback;
  	}
    }
  while (*string++);
  return chksum;
}