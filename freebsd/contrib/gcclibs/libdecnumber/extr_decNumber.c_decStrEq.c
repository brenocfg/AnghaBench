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
typedef  int Flag ;

/* Variables and functions */
 scalar_t__ tolower (unsigned char) ; 

__attribute__((used)) static Flag
decStrEq (const char *str1, const char *str2)
{
  for (;; str1++, str2++)
    {
      unsigned char u1 = (unsigned char) *str1;
      unsigned char u2 = (unsigned char) *str2;
      if (u1 == u2)
	{
	  if (u1 == '\0')
	    break;
	}
      else
	{
	  if (tolower (u1) != tolower (u2))
	    return 0;
	}
    }				/* stepping */
  return 1;
}