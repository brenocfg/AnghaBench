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
 int errno ; 
 int /*<<< orphan*/  strerror (int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  xstrlcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static const char *
expand_error(const char *f, char *e, size_t maxlen)
{
  const char *p;
  char *q;
  int error = errno;
  size_t len = 0, l;

  *e = '\0';
  for (p = f, q = e; len < maxlen && (*q = *p); len++, q++, p++) {
    if (p[0] == '%' && p[1] == 'm') {
      if (len >= maxlen)
	break;
      xstrlcpy(q, strerror(error), maxlen - len);
      l = strlen(q);
      if (l != 0)
	  l--;
      len += l;
      q += l;
      p++;
    }
  }
  e[maxlen - 1] = '\0';		/* null terminate, to be sure */
  return e;
}