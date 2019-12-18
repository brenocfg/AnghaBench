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
typedef  int /*<<< orphan*/  voidp ;
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct in_addr {scalar_t__ s_addr; } ;
struct hostent {int /*<<< orphan*/ ** h_addr_list; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  dq ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  dlog (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_myaddress (struct sockaddr_in*) ; 
 struct hostent* gethostbyname (char const*) ; 
 int /*<<< orphan*/  h_errno ; 
 int /*<<< orphan*/  hstrerror (int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_dquad (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char const*,...) ; 

void
amu_get_myaddress(struct in_addr *iap, const char *preferred_localhost)
{
  struct hostent *hp;
  char dq[20];

#ifdef DEBUG_off
#error this code is old and probably not useful any longer.
#error Erez, Jan 21, 2004.
  struct sockaddr_in sin;

  /*
   * Most modern systems should use 127.0.0.1 as the localhost address over
   * which you can do NFS mounts.  In the past we found that some NFS
   * clients may not allow mounts from localhost.  So we used
   * get_myaddress() and that seemed to work.  Alas, on some other systems,
   * get_myaddress() may return one of the interface addresses at random,
   * and thus use a less efficient IP address than 127.0.0.1.  The solution
   * is to hard-code 127.0.0.1, but still check if get_myaddress() returns a
   * different value and warn about it.
   */
  memset((char *) &sin, 0, sizeof(sin));
  get_myaddress(&sin);
  if (sin.sin_addr.s_addr != htonl(INADDR_LOOPBACK))
    dlog("amu_get_myaddress: myaddress conflict (0x%x vs. 0x%lx)",
	 sin.sin_addr.s_addr, (u_long) htonl(INADDR_LOOPBACK));
#endif /* DEBUG_off */

  if (preferred_localhost == NULL)
    goto out;

  /* if specified preferred locahost, then try to use it */
  hp = gethostbyname(preferred_localhost);
  if (hp == NULL) {
    /* XXX: if hstrerror()/h_errno aren't portable, then need to port the next statement */
    plog(XLOG_ERROR, "Unable to resolve localhost_address \"%s\" (%s): using default",
	 preferred_localhost, hstrerror(h_errno));
    goto out;
  }
  if (hp->h_addr_list == NULL) {
    plog(XLOG_ERROR, "localhost_address \"%s\" has no IP addresses: using default",
	 preferred_localhost);
    goto out;
  }
  if (hp->h_addr_list[1] != NULL) {
    plog(XLOG_ERROR, "localhost_address \"%s\" has more than one IP addresses: using first",
	 preferred_localhost);
    goto out;
  }
  memmove((voidp) &iap->s_addr, (voidp) hp->h_addr_list[0], sizeof(iap->s_addr));
  plog(XLOG_INFO, "localhost_address \"%s\" requested, using %s",
       preferred_localhost, inet_dquad(dq, sizeof(dq), iap->s_addr));
  return;

 out:
  iap->s_addr = htonl(INADDR_LOOPBACK);
}