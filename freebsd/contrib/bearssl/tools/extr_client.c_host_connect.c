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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; scalar_t__ ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int SOCKET ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int INVALID_SOCKET ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (int) ; 
 int connect (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,void*,char*,int) ; 
 int /*<<< orphan*/  ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int
host_connect(const char *host, const char *port, int verbose)
{
	struct addrinfo hints, *si, *p;
	SOCKET fd;
	int err;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	err = getaddrinfo(host, port, &hints, &si);
	if (err != 0) {
		fprintf(stderr, "ERROR: getaddrinfo(): %s\n",
			gai_strerror(err));
		return INVALID_SOCKET;
	}
	fd = INVALID_SOCKET;
	for (p = si; p != NULL; p = p->ai_next) {
		if (verbose) {
			struct sockaddr *sa;
			void *addr;
			char tmp[INET6_ADDRSTRLEN + 50];

			sa = (struct sockaddr *)p->ai_addr;
			if (sa->sa_family == AF_INET) {
				addr = &((struct sockaddr_in *)
					(void *)sa)->sin_addr;
			} else if (sa->sa_family == AF_INET6) {
				addr = &((struct sockaddr_in6 *)
					(void *)sa)->sin6_addr;
			} else {
				addr = NULL;
			}
			if (addr != NULL) {
				if (!inet_ntop(p->ai_family, addr,
					tmp, sizeof tmp))
				{
					strcpy(tmp, "<invalid>");
				}
			} else {
				sprintf(tmp, "<unknown family: %d>",
					(int)sa->sa_family);
			}
			fprintf(stderr, "connecting to: %s\n", tmp);
		}
		fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (fd == INVALID_SOCKET) {
			if (verbose) {
				perror("socket()");
			}
			continue;
		}
		if (connect(fd, p->ai_addr, p->ai_addrlen) == INVALID_SOCKET) {
			if (verbose) {
				perror("connect()");
			}
#ifdef _WIN32
			closesocket(fd);
#else
			close(fd);
#endif
			continue;
		}
		break;
	}
	if (p == NULL) {
		freeaddrinfo(si);
		fprintf(stderr, "ERROR: failed to connect\n");
		return INVALID_SOCKET;
	}
	freeaddrinfo(si);
	if (verbose) {
		fprintf(stderr, "connected.\n");
	}

	/*
	 * We make the socket non-blocking, since we are going to use
	 * poll() or select() to organise I/O.
	 */
#ifdef _WIN32
	{
		u_long arg;

		arg = 1;
		ioctlsocket(fd, FIONBIO, &arg);
	}
#else
	fcntl(fd, F_SETFL, O_NONBLOCK);
#endif
	return fd;
}