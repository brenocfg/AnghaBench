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
typedef  int /*<<< orphan*/  u_int ;
struct opt_tab {int /*<<< orphan*/  flag; scalar_t__ opt; } ;

/* Variables and functions */
 scalar_t__ STREQ (char*,scalar_t__) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*) ; 
 char* strchr (char*,char) ; 

int
cmdoption(char *s, struct opt_tab *optb, u_int *flags)
{
  char *p = s;
  int errs = 0;

  while (p && *p) {
    int neg;
    char *opt;
    struct opt_tab *dp, *dpn = NULL;

    s = p;
    p = strchr(p, ',');
    if (p)
      *p = '\0';

    /* check for "no" prefix to options */
    if (s[0] == 'n' && s[1] == 'o') {
      opt = s + 2;
      neg = 1;
    } else {
      opt = s;
      neg = 0;
    }

    /*
     * Scan the array of debug options to find the
     * corresponding flag value.  If it is found
     * then set (or clear) the flag (depending on
     * whether the option was prefixed with "no").
     */
    for (dp = optb; dp->opt; dp++) {
      if (STREQ(opt, dp->opt))
	break;
      if (opt != s && !dpn && STREQ(s, dp->opt))
	dpn = dp;
    }

    if (dp->opt || dpn) {
      if (!dp->opt) {
	dp = dpn;
	neg = !neg;
      }
      if (neg)
	*flags &= ~dp->flag;
      else
	*flags |= dp->flag;
    } else {
      /*
       * This will log to stderr when parsing the command line
       * since any -l option will not yet have taken effect.
       */
      plog(XLOG_ERROR, "option \"%s\" not recognized", s);
      errs++;
    }

    /*
     * Put the comma back
     */
    if (p)
      *p++ = ',';
  }

  return errs;
}