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
struct hostent {char* h_name; char** h_aliases; } ;

/* Variables and functions */
 scalar_t__ STREQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  dlog (char*,char*,...) ; 
 struct hostent* gethostbyname (char*) ; 
 char* h_errno ; 
 char* hstrerror (char*) ; 
 int /*<<< orphan*/  opt_hostd ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int
f_xhost(char *arg)
{
  struct hostent *hp;
  char **cp;

  if (!arg)
    return 0;

  /* simple test: does it match main host name? */
  if (STREQ(arg, opt_hostd))
    return 1;

  /* now find all of the names of "arg" and compare against opt_hostd */
  hp = gethostbyname(arg);
  if (hp == NULL) {
#ifdef HAVE_HSTRERROR
    plog(XLOG_ERROR, "gethostbyname xhost(%s): %s", arg, hstrerror(h_errno));
#else /* not HAVE_HSTRERROR */
    plog(XLOG_ERROR, "gethostbyname xhost(%s): h_errno %d", arg, h_errno);
#endif /* not HAVE_HSTRERROR */
    return 0;
  }
  /* check primary name */
  if (hp->h_name) {
    dlog("xhost: compare %s==%s", hp->h_name, opt_hostd);
    if (STREQ(hp->h_name, opt_hostd)) {
      plog(XLOG_INFO, "xhost(%s): matched h_name %s", arg, hp->h_name);
      return 1;
    }
  }
  /* check all aliases, if any */
  if (hp->h_aliases == NULL) {
    dlog("gethostbyname(%s) has no aliases", arg);
    return 0;
  }
  cp = hp->h_aliases;
  while (*cp) {
    dlog("xhost: compare alias %s==%s", *cp, opt_hostd);
    if (STREQ(*cp, opt_hostd)) {
      plog(XLOG_INFO, "xhost(%s): matched alias %s", arg, *cp);
      return 1;
    }
    cp++;
  }
  /* nothing matched */
  return 0;
}