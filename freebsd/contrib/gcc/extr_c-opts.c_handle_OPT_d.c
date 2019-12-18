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
 int flag_dump_includes ; 
 char flag_dump_macros ; 

__attribute__((used)) static void
handle_OPT_d (const char *arg)
{
  char c;

  while ((c = *arg++) != '\0')
    switch (c)
      {
      case 'M':			/* Dump macros only.  */
      case 'N':			/* Dump names.  */
      case 'D':			/* Dump definitions.  */
	flag_dump_macros = c;
	break;

      case 'I':
	flag_dump_includes = 1;
	break;
      }
}