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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct hostent {scalar_t__ h_addr; } ;
typedef  int /*<<< orphan*/  host_addr ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  MOUNTPROG ; 
 int /*<<< orphan*/  MOUNTVERS ; 
 int RPC_ANYSOCK ; 
 int /*<<< orphan*/  RPC_TIMEDOUT ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  STREQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  before_rpc ; 
 int /*<<< orphan*/ * clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clnt_pcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_perrno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clnttcp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clntudp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval,int*) ; 
 int /*<<< orphan*/  create_timeout ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  localhost ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int privsock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quiet ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ualarm (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CLIENT *
clnt_create_timeout(char *host, struct timeval *tvp)
{
  CLIENT *clnt;
  struct sockaddr_in host_addr;
  struct hostent *hp;
#ifndef HAVE_TRANSPORT_TYPE_TLI
  int s;
#endif /* not HAVE_TRANSPORT_TYPE_TLI */

  if (setjmp(before_rpc)) {
    if (!quiet) {
      fprintf(stderr, "%s: ", host);
      clnt_perrno(RPC_TIMEDOUT);
      fprintf(stderr, "\n");
      fflush(stderr);
    }
    return NULL;
  }
  signal(SIGALRM, create_timeout);
  ualarm(tvp->tv_sec * 1000000 + tvp->tv_usec, 0);

  /*
   * Get address of host
   */
  if ((hp = gethostbyname(host)) == 0 && !STREQ(host, localhost)) {
    fprintf(stderr, "can't get address of %s\n", host);
    return NULL;
  }
  memset(&host_addr, 0, sizeof(host_addr));
  /* as per POSIX, sin_len need not be set (used internally by kernel) */
  host_addr.sin_family = AF_INET;
  if (hp) {
    memmove((voidp) &host_addr.sin_addr, (voidp) hp->h_addr,
	    sizeof(host_addr.sin_addr));
  } else {
    /* fake "localhost" */
    host_addr.sin_addr.s_addr = htonl(0x7f000001);
  }

#ifdef HAVE_TRANSPORT_TYPE_TLI
  /* try TCP first (in case return data is large), then UDP */
  clnt = clnt_create(host, MOUNTPROG, MOUNTVERS, "tcp");
  if (!clnt)
    clnt = clnt_create(host, MOUNTPROG, MOUNTVERS, "udp");
#else /* not HAVE_TRANSPORT_TYPE_TLI */
  s = RPC_ANYSOCK;
  clnt = clnttcp_create(&host_addr, MOUNTPROG, MOUNTVERS, &s, 0, 0);
  if (!clnt) {
    /* XXX: do we need to close(s) ? */
    s = privsock(SOCK_DGRAM);
    clnt = clntudp_create(&host_addr, MOUNTPROG, MOUNTVERS, *tvp, &s);
  }
#endif /* not HAVE_TRANSPORT_TYPE_TLI */

  if (!clnt) {
    ualarm(0, 0);
    if (!quiet) {
      clnt_pcreateerror(host);
      fflush(stderr);
    }
    return NULL;
  }

  ualarm(0, 0);
  return clnt;
}