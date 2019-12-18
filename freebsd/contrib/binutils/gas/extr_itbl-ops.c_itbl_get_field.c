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
 int /*<<< orphan*/  ASSERT (int) ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

char *
itbl_get_field (char **S)
{
  static char n[128];
  char *s;
  int len;

  s = *S;
  if (!s || !*s)
    return 0;
  /* FIXME: This is a weird set of delimiters.  */
  len = strcspn (s, " \t,()");
  ASSERT (128 > len + 1);
  strncpy (n, s, len);
  n[len] = 0;
  if (s[len] == '\0')
    s = 0;			/* no more args */
  else
    s += len + 1;		/* advance to next arg */

  *S = s;
  return n;
}