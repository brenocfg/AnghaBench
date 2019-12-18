#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CFM_NORMALIZE_SLASHES ; 
 TYPE_1__ gopt ; 
 char* strchr (char*,char) ; 

void
normalize_slash(char *p)
{
  char *f, *f0;

  if (!(gopt.flags & CFM_NORMALIZE_SLASHES))
    return;

  f0 = f = strchr(p, '/');
  if (f) {
    char *t = f;
    do {
      /* assert(*f == '/'); */
      if (f == f0 && f[0] == '/' && f[1] == '/') {
	/* copy double slash iff first */
	*t++ = *f++;
	*t++ = *f++;
      } else {
	/* copy a single / across */
	*t++ = *f++;
      }

      /* assert(f[-1] == '/'); */
      /* skip past more /'s */
      while (*f == '/')
	f++;

      /* assert(*f != '/'); */
      /* keep copying up to next / */
      while (*f && *f != '/') {
	/* support escaped slashes '\/' */
	if (f[0] == '\\' && f[1] == '/')
	  f++;			/* skip backslash */
	*t++ = *f++;
      }

      /* assert(*f == 0 || *f == '/'); */

    } while (*f);
    *t = '\0';			/* derived from fix by Steven Glassman */
  }
}