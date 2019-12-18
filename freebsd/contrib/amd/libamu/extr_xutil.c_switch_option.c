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
typedef  int u_int ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int XLOG_MANDATORY ; 
 int cmdoption (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int xlog_level ; 
 int /*<<< orphan*/  xlog_opt ; 

int
switch_option(char *opt)
{
  u_int xl = xlog_level;
  int rc = cmdoption(opt, xlog_opt, &xl);

  if (rc)			/* if got any error, don't update flags */
    return EINVAL;

  /*
   * Don't allow "mandatory" flags to be turned off, because
   * we must always be able to report on flag re/setting errors.
   */
  if ((xl & XLOG_MANDATORY) != XLOG_MANDATORY) {
    plog(XLOG_ERROR, "cannot turn off mandatory logging options");
    xl |= XLOG_MANDATORY;
  }
  if (xlog_level != xl)
    xlog_level = xl;		/* set new flags */
  return rc;
}