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
 int fromhex (char const) ; 

__attribute__((used)) static int
hex2bin (const char *hex, char *bin, int count)
{
  int i;

  for (i = 0; i < count; i++)
    {
      if (hex[0] == 0 || hex[1] == 0)
	{
	  /* Hex string is short, or of uneven length.
	     Return the count that has been converted so far. */
	  return i;
	}
      *bin++ = fromhex (hex[0]) * 16 + fromhex (hex[1]);
      hex += 2;
    }
  return i;
}