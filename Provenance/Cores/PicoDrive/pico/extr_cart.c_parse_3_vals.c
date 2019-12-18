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
 char* sskip (char*) ; 
 int strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_3_vals(char *p, int *val0, int *val1, int *val2)
{
  char *r;
  *val0 = strtoul(p, &r, 0);
  if (r == p)
    goto bad;
  p = sskip(r);
  if (*p++ != ',')
    goto bad;
  *val1 = strtoul(p, &r, 0);
  if (r == p)
    goto bad;
  p = sskip(r);
  if (*p++ != ',')
    goto bad;
  *val2 = strtoul(p, &r, 0);
  if (r == p)
    goto bad;

  return 1;
bad:
  return 0;
}