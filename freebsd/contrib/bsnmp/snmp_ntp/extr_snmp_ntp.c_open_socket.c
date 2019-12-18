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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EADDRNOTAVAIL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntp_host ; 
 int /*<<< orphan*/  ntp_port ; 
 int ntpd_sock ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static int
open_socket(void)
{
	struct addrinfo hints, *res, *res0;
	int	error;
	const char *cause;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	error = getaddrinfo(ntp_host, ntp_port, &hints, &res0);
	if (error) {
		syslog(LOG_ERR, "%s(%s): %s", ntp_host, ntp_port,
		    gai_strerror(error));
		return (-1);
	}

	ntpd_sock = -1;
	cause = "no address";
	errno = EADDRNOTAVAIL;
	for (res = res0; res != NULL; res = res->ai_next) {
		ntpd_sock = socket(res->ai_family, res->ai_socktype,
		    res->ai_protocol);
		if (ntpd_sock == -1) {
			cause = "socket";
			continue;
		}
		if (connect(ntpd_sock, res->ai_addr, res->ai_addrlen) == -1) {
			cause = "connect";
			(void)close(ntpd_sock);
			ntpd_sock = -1;
			continue;
		}
		break;
	}
	if (ntpd_sock == -1) {
		syslog(LOG_ERR, "%s: %m", cause);
		return (-1);
	}
	freeaddrinfo(res0);
	return (0);
}