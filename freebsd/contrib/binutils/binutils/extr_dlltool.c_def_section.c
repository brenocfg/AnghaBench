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
 int /*<<< orphan*/  new_directive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

void
def_section (const char *name, int attr)
{
  char buf[200];
  char atts[5];
  char *d = atts;
  if (attr & 1)
    *d++ = 'R';

  if (attr & 2)
    *d++ = 'W';
  if (attr & 4)
    *d++ = 'X';
  if (attr & 8)
    *d++ = 'S';
  *d++ = 0;
  sprintf (buf, "-attr %s %s", name, atts);
  new_directive (xstrdup (buf));
}