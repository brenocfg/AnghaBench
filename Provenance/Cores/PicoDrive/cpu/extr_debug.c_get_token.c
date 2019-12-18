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
 scalar_t__ isspace_ (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static const char *get_token(char *buf, int blen, const char *str)
{
  const char *p, *s, *e;
  int len;

  p = str;
  while (isspace_(*p))
    p++;
  if (*p == 0)
    return NULL;
  if (*p == ';') {
    strcpy(buf, ";");
    return p + 1;
  }

  s = p;
  while (*p != 0 && *p != ';' && !isspace_(*p))
    p++;
  e = p;
  while (isspace_(*e))
    e++;

  len = p - s;
  if (len > blen - 1)
    len = blen - 1;
  memcpy(buf, s, len);
  buf[len] = 0;
  return e;
}