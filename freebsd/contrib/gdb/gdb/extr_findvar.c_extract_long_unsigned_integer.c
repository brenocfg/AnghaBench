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
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 int /*<<< orphan*/  extract_unsigned_integer (char*,int) ; 

int
extract_long_unsigned_integer (const void *addr, int orig_len, LONGEST *pval)
{
  char *p, *first_addr;
  int len;

  len = orig_len;
  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    {
      for (p = (char *) addr;
	   len > (int) sizeof (LONGEST) && p < (char *) addr + orig_len;
	   p++)
	{
	  if (*p == 0)
	    len--;
	  else
	    break;
	}
      first_addr = p;
    }
  else
    {
      first_addr = (char *) addr;
      for (p = (char *) addr + orig_len - 1;
	   len > (int) sizeof (LONGEST) && p >= (char *) addr;
	   p--)
	{
	  if (*p == 0)
	    len--;
	  else
	    break;
	}
    }

  if (len <= (int) sizeof (LONGEST))
    {
      *pval = (LONGEST) extract_unsigned_integer (first_addr,
						  sizeof (LONGEST));
      return 1;
    }

  return 0;
}