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
 int HASHWORDBITS ; 

unsigned long int
__hash_string (const char *str_param)
{
  unsigned long int hval, g;
  const char *str = str_param;

  /* Compute the hash value for the given string.  */
  hval = 0;
  while (*str != '\0')
    {
      hval <<= 4;
      hval += (unsigned char) *str++;
      g = hval & ((unsigned long int) 0xf << (HASHWORDBITS - 4));
      if (g != 0)
	{
	  hval ^= g >> (HASHWORDBITS - 8);
	  hval ^= g;
	}
    }
  return hval;
}