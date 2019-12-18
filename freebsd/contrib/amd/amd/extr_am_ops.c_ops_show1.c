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
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  xstrlcat (char*,char const*,size_t) ; 

__attribute__((used)) static void
ops_show1(char *buf, size_t l, int *linesizep, const char *name)
{
  xstrlcat(buf, name, l);
  xstrlcat(buf, ", ", l);
  *linesizep += strlen(name) + 2;
  if (*linesizep > 60) {
    xstrlcat(buf, "\t\n", l);
    *linesizep = 0;
  }
}