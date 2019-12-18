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
 int PATH_MAX ; 
 int /*<<< orphan*/  cygwin_conv_to_posix_path (char*,char*) ; 
 char* default_nto_target ; 
 char* getenv (char*) ; 

__attribute__((used)) static char *
nto_target (void)
{
  char *p = getenv ("QNX_TARGET");

#ifdef __CYGWIN__
  static char buf[PATH_MAX];
  if (p)
    cygwin_conv_to_posix_path (p, buf);
  else
    cygwin_conv_to_posix_path (default_nto_target, buf);
  return buf;
#else
  return p ? p : default_nto_target;
#endif
}