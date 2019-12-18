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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  map_option_f ; 

void
lang_add_map (const char *name)
{
  while (*name)
    {
      switch (*name)
	{
	case 'F':
	  map_option_f = TRUE;
	  break;
	}
      name++;
    }
}