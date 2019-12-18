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
 int /*<<< orphan*/  memcpy (long*,char*,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 

__attribute__((used)) static void
dump_mem (char *buf, int len)
{
  if (len <= 8)
    {
      if (len == 8 || len == 4)
	{
	  long l[2];
	  memcpy (l, buf, len);
	  printf_filtered ("\t0x%lx", l[0]);
	  if (len == 8)
	    printf_filtered (" 0x%lx", l[1]);
	  printf_filtered ("\n");
	}
      else
	{
	  int i;
	  printf_filtered ("\t");
	  for (i = 0; i < len; i++)
	    printf_filtered ("0x%x ", buf[i]);
	  printf_filtered ("\n");
	}
    }
}