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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int MINISSDPC_SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

int
connectToMiniSSDPD(const char * socketpath)
{
	int s;
	struct sockaddr_un addr;
#if defined(MINIUPNPC_SET_SOCKET_TIMEOUT) && !defined(__sun)
	struct timeval timeout;
#endif /* #ifdef MINIUPNPC_SET_SOCKET_TIMEOUT */

	s = socket(AF_UNIX, SOCK_STREAM, 0);
	if(s < 0)
	{
		/*syslog(LOG_ERR, "socket(unix): %m");*/
		perror("socket(unix)");
		return MINISSDPC_SOCKET_ERROR;
	}
#if defined(MINIUPNPC_SET_SOCKET_TIMEOUT) && !defined(__sun)
	/* setting a 3 seconds timeout */
	/* not supported for AF_UNIX sockets under Solaris */
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	if(setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)) < 0)
	{
		perror("setsockopt SO_RCVTIMEO unix");
	}
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	if(setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval)) < 0)
	{
		perror("setsockopt SO_SNDTIMEO unix");
	}
#endif /* #ifdef MINIUPNPC_SET_SOCKET_TIMEOUT */
	if(!socketpath)
		socketpath = "/var/run/minissdpd.sock";
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socketpath, sizeof(addr.sun_path));
	/* TODO : check if we need to handle the EINTR */
	if(connect(s, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0)
	{
		/*syslog(LOG_WARNING, "connect(\"%s\"): %m", socketpath);*/
		close(s);
		return MINISSDPC_SOCKET_ERROR;
	}
	return s;
}