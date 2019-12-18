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
 int BUF_LEN ; 

__attribute__((used)) static char *
safe_concat (char *buf, char *cur, const char *str)
{
  char *end = buf + BUF_LEN - 2;	/* Leave room for null.  */
  int c;

  if (cur > end)
    {
      *end = '\0';
      return end;
    }

  while (cur < end && (c = *str++) != '\0')
    *cur++ = c;

  *cur = '\0';
  return cur;
}