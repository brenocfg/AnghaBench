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

__attribute__((used)) static int
n_sep_els (const char *s, int sep, int par_flag)
{
  int n;
  int pars_num;

  if (*s == '\0')
    return 0;

  for (pars_num = 0, n = 1; *s; s++)
    if (par_flag && *s == '(')
      pars_num++;
    else if (par_flag && *s == ')')
      pars_num--;
    else if (pars_num == 0 && *s == sep)
      n++;

  return (pars_num != 0 ? -1 : n);
}