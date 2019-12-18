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
typedef  int u_long ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int socklen_t ;
typedef  int SOCKET ;
typedef  int /*<<< orphan*/  SOCKADDR_STORAGE ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* inet_ntop (int const,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static SOCKET
accept_client(SOCKET server_fd, int verbose, int nonblock)
{
	int fd;
	SOCKADDR_STORAGE sa;
	socklen_t sa_len;

	sa_len = sizeof sa;
	fd = accept(server_fd, (struct sockaddr *)&sa, &sa_len);
	if (fd == INVALID_SOCKET) {
		if (verbose) {
			perror("accept()");
		}
		return INVALID_SOCKET;
	}
	if (verbose) {
		char tmp[INET6_ADDRSTRLEN + 50];
		const char *name;

		name = NULL;
		switch (((struct sockaddr *)&sa)->sa_family) {
		case AF_INET:
			name = inet_ntop(AF_INET,
				&((struct sockaddr_in *)&sa)->sin_addr,
				tmp, sizeof tmp);
			break;
		case AF_INET6:
			name = inet_ntop(AF_INET6,
				&((struct sockaddr_in6 *)&sa)->sin6_addr,
				tmp, sizeof tmp);
			break;
		}
		if (name == NULL) {
			sprintf(tmp, "<unknown: %lu>", (unsigned long)
				((struct sockaddr *)&sa)->sa_family);
			name = tmp;
		}
		fprintf(stderr, "accepting connection from: %s\n", name);
	}

	/*
	 * We make the socket non-blocking, since we are going to use
	 * poll() or select() to organise I/O.
	 */
	if (nonblock) {
#ifdef _WIN32
		u_long arg;

		arg = 1;
		ioctlsocket(fd, FIONBIO, &arg);
#else
		fcntl(fd, F_SETFL, O_NONBLOCK);
#endif
	}
	return fd;
}