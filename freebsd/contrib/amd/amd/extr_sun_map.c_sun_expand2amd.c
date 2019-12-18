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
 int /*<<< orphan*/  AMD_ARCH ; 
 int /*<<< orphan*/  AMD_HOST ; 
 int /*<<< orphan*/  AMD_OSNAME ; 
 int /*<<< orphan*/  AMD_OSVER ; 
 int /*<<< orphan*/  SUN_ARCH ; 
 int /*<<< orphan*/  SUN_CPU ; 
 int /*<<< orphan*/  SUN_HOST ; 
 int /*<<< orphan*/  SUN_NATISA ; 
 int /*<<< orphan*/  SUN_OSNAME ; 
 int /*<<< orphan*/  SUN_OSREL ; 
 int /*<<< orphan*/  SUN_OSVERS ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 char* sun_strsub (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *
sun_expand2amd(const char *str)
{

  char *retval = NULL, *tmp = NULL, *tmp2 = NULL;
  const char *pos;

  /*
   * Iterator through the string looking for '$' chars.  For each '$'
   * found try to replace it with Sun variable substitutions.  If we
   * find a '$' that is not a substation each of the i.e $blah than
   * each of the replace attempt will fail and we'll move on to the
   * next char.
   */
  tmp = xstrdup(str);
  for (pos = str; *pos != '\0'; pos++) {
    if (*pos != '$') {
      continue;
    }
    if (tmp2 != NULL) {
      XFREE(tmp);
      tmp = tmp2;
    }

    /*
     * If a 'replace' does not return NULL than a variable was
     * successfully substituted.
     */

    /* architecture */
    if ((tmp2 = sun_strsub(tmp, SUN_ARCH, AMD_ARCH)) != NULL) {
      continue;
    }
    /* cpu - there is not POSIX uname for cpu so just use machine */
    if ((tmp2 = sun_strsub(tmp, SUN_CPU, AMD_ARCH)) != NULL) {
      continue;
    }
    /* hostname */
    if ((tmp2 = sun_strsub(tmp, SUN_HOST, AMD_HOST)) != NULL) {
      continue;
    }
    /* os name */
    if ((tmp2 = sun_strsub(tmp, SUN_OSNAME, AMD_OSNAME)) != NULL) {
      continue;
    }
    /*
     * os release - Amd doesn't hava a OS release var just usr os
     * version or now.
     */
    if ((tmp2 = sun_strsub(tmp, SUN_OSREL, AMD_OSVER)) != NULL) {
      continue;
    }
    /* os version */
    if ((tmp2 = sun_strsub(tmp, SUN_OSVERS, AMD_OSVER)) != NULL) {
      continue;
    }
    /* native instruction set - there is no POSIX natisa so just use system */
    if ((tmp2 = sun_strsub(tmp, SUN_NATISA, AMD_ARCH)) != NULL) {
      continue;
    }
  }
  if (tmp2 == NULL) {
    retval = tmp;
  }
  else {
    retval = tmp2;
    XFREE(tmp);
  }

  return retval;
}