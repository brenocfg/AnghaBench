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
struct trans {int val; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
trans(const struct trans t[], const char *arg)
{
  int f;

  for (f = 0; t[f].val != -1; f++)
    if (!strncasecmp(t[f].str, arg, 3) ||
        !strncasecmp(t[f].str, arg, strlen(t[f].str)))
      return t[f].val;

  return -1;
}