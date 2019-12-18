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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; TYPE_1__ sin_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin6_addr; TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct addrinfo {size_t ai_addrlen; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; scalar_t__ ai_addr; struct addrinfo* ai_next; } ;
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,void*,char*,int) ; 
 scalar_t__ listen (scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_in6*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static SOCKET
host_bind(const char *host, const char *port, int verbose)
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
		struct sockaddr *sa;
		struct sockaddr_in sa4;
		struct sockaddr_in6 sa6;
		size_t sa_len;
		void *addr;
		int opt;

		sa = (struct sockaddr *)p->ai_addr;
		if (sa->sa_family == AF_INET) {
			memcpy(&sa4, sa, sizeof sa4);
			sa = (struct sockaddr *)&sa4;
			sa_len = sizeof sa4;
			addr = &sa4.sin_addr;
			if (host == NULL) {
				sa4.sin_addr.s_addr = INADDR_ANY;
			}
		} else if (sa->sa_family == AF_INET6) {
			memcpy(&sa6, sa, sizeof sa6);
			sa = (struct sockaddr *)&sa6;
			sa_len = sizeof sa6;
			addr = &sa6.sin6_addr;
			if (host == NULL) {
				sa6.sin6_addr = in6addr_any;
			}
		} else {
			addr = NULL;
			sa_len = p->ai_addrlen;
		}
		if (verbose) {
			char tmp[INET6_ADDRSTRLEN + 50];

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
			fprintf(stderr, "binding to: %s\n", tmp);
		}
		fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (fd == INVALID_SOCKET) {
			if (verbose) {
				perror("socket()");
			}
			continue;
		}
		opt = 1;
		setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
			(void *)&opt, sizeof opt);
#ifdef IPV6_V6ONLY
		/*
		 * We want to make sure that the server socket works for
		 * both IPv4 and IPv6. But IPV6_V6ONLY is not defined on
		 * some very old systems.
		 */
		opt = 0;
		setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY,
			(void *)&opt, sizeof opt);
#endif
		if (bind(fd, sa, sa_len) < 0) {
			if (verbose) {
				perror("bind()");
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
		fprintf(stderr, "ERROR: failed to bind\n");
		return INVALID_SOCKET;
	}
	freeaddrinfo(si);
	if (listen(fd, 5) < 0) {
		if (verbose) {
			perror("listen()");
		}
#ifdef _WIN32
		closesocket(fd);
#else
		close(fd);
#endif
		return INVALID_SOCKET;
	}
	if (verbose) {
		fprintf(stderr, "bound.\n");
	}
	return fd;
}