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
typedef  int /*<<< orphan*/  u_long ;
struct timeval {int dummy; } ;
struct sockaddr_in {scalar_t__ sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  MOUNTPROG ; 
 int RPC_ANYSOCK ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 scalar_t__ bind_resv_port (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clnttcp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clntudp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  dlog (char*,scalar_t__) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pmap_getport (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

CLIENT *
get_mount_client(char *unused_host, struct sockaddr_in *sin, struct timeval *tv, int *sock, u_long mnt_version)
{
  CLIENT *client;

  /*
   * First try a TCP socket
   */
  if ((*sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) > 0) {
    /*
     * Bind to a privileged port
     */
    if (bind_resv_port(*sock, (u_short *) NULL) < 0)
      plog(XLOG_ERROR, "can't bind privileged port (socket)");

    /*
     * Find mountd port to connect to.
     * Connect to mountd.
     * Create a tcp client.
     */
    if ((sin->sin_port = htons(pmap_getport(sin, MOUNTPROG, mnt_version, IPPROTO_TCP))) != 0) {
      if (connect(*sock, (struct sockaddr *) sin, sizeof(*sin)) >= 0
	  && ((client = clnttcp_create(sin, MOUNTPROG, mnt_version, sock, 0, 0)) != NULL))
	return client;
    }
    /*
     * Failed so close socket
     */
    (void) close(*sock);
  }				/* tcp socket opened */
  /* TCP failed so try UDP */
  if ((*sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    plog(XLOG_ERROR, "Can't create socket to connect to mountd: %m");
    *sock = RPC_ANYSOCK;
    return NULL;
  }
  /*
   * Bind to a privileged port
   */
  if (bind_resv_port(*sock, (u_short *) NULL) < 0)
    plog(XLOG_ERROR, "can't bind privileged port");

  /*
   * Zero out the port - make sure we recompute
   */
  sin->sin_port = 0;

  /*
   * Make a UDP client
   */
  if ((client = clntudp_create(sin, MOUNTPROG, mnt_version, *tv, sock)) == NULL) {
    (void) close(*sock);
    *sock = RPC_ANYSOCK;
    return NULL;
  }
  dlog("get_mount_client: Using udp, port %d", sin->sin_port);
  return client;
}