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
 int strlen (char*) ; 

char *
hasmnteq(mntent_t *mnt, char *opt)
{
  if (mnt && opt) {		/* disallow null input pointers */
    if ( *opt ) {		/* disallow the null string as an opt */
      char *str = amu_hasmntopt(mnt, opt);
      if ( str ) {		/* option was there */
	char *eq = str + strlen(opt); /* Look at char just after option */
	if (*eq == '=')		/* Is it '=' ? */
	  return ++eq;		/* If so, return pointer to remaining str */
      }
    }
  }
  return NULL;
}