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
read_pe_truncate_name (char *dll_name)
{
  while (*dll_name)
    {
      if ((*dll_name) == '.')
	{
	  *dll_name = '\0';	/* truncates and causes loop exit. */
	}

      else
	{
	  ++dll_name;
	}
    }
}