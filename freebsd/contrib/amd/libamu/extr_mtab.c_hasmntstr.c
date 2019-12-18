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
typedef  int /*<<< orphan*/  mntent_t ;

/* Variables and functions */
 char* amu_hasmntopt (int /*<<< orphan*/ *,char*) ; 
 char* hasmnteq (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* xmalloc (int) ; 
 char* xstrdup (char*) ; 

char *
hasmntstr(mntent_t *mnt, char *opt)
{
  char *str = amu_hasmntopt(mnt, opt);

  if (str) { /* The option was there */

    char *eq = hasmnteq(mnt, opt);

    if (eq) { /* and had an = after it */

      char *endptr = strchr(eq, ',');

      /* if saw no comma, return xstrdup'd string */
      if (!endptr)
	return xstrdup(eq);
      else {
	/* else we need to copy only the chars needed */
	int len = endptr - eq;
	char *buf = xmalloc(len + 1);
	strncpy(buf, eq, len);
	buf[len] = '\0';
	return buf;
      }
    }
  }
  return NULL;
}