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
typedef  int /*<<< orphan*/  u_short ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  FNDELAY ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 scalar_t__ bind_resv_port (scalar_t__,int /*<<< orphan*/ *) ; 
 int errno ; 
 scalar_t__ fcntl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fwd_sock ; 
 scalar_t__ ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * t_errlist ; 
 size_t t_errno ; 
 scalar_t__ t_open (char*,int,int /*<<< orphan*/ ) ; 

int
fwd_init(void)
{
#ifdef FIONBIO
  int on = 1;
#endif /* FIONBIO */

#ifdef HAVE_TRANSPORT_TYPE_TLI
  /*
   * Create ping TLI socket (/dev/tcp and /dev/ticlts did not work)
   * (HPUX-11 does not like using O_NDELAY in flags)
   */
  fwd_sock = t_open("/dev/udp", O_RDWR|O_NONBLOCK, 0);
  if (fwd_sock < 0) {
    plog(XLOG_ERROR, "unable to create RPC forwarding TLI socket: %s",
	 t_errlist[t_errno]);
    return errno;
  }
#else /* not HAVE_TRANSPORT_TYPE_TLI */
  /*
   * Create ping socket
   */
  fwd_sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (fwd_sock < 0) {
    plog(XLOG_ERROR, "unable to create RPC forwarding socket: %m");
    return errno;
  }
#endif /* not HAVE_TRANSPORT_TYPE_TLI */

  /*
   * Some things we talk to require a priv port - so make one here
   */
  if (bind_resv_port(fwd_sock, (u_short *) NULL) < 0)
    plog(XLOG_ERROR, "can't bind privileged port (rpc_fwd)");

  if (fcntl(fwd_sock, F_SETFL, FNDELAY) < 0
#ifdef FIONBIO
      && ioctl(fwd_sock, FIONBIO, &on) < 0
#endif /* FIONBIO */
    ) {
    plog(XLOG_ERROR, "Can't set non-block on forwarding socket: %m");
    return errno;
  }

  return 0;
}