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

char *
ada_start_decode_line_1 (char *line)
{
  /* [NOTE: strpbrk would be more elegant, but I am reluctant to be
     the first to use such a library function in GDB code.] */
  char *p;
  for (p = line; *p != '\000' && *p != ' ' && *p != ':'; p += 1)
    ;
  return p;
}