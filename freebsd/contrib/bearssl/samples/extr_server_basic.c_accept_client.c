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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int socklen_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  INET6_ADDRSTRLEN ; 
 int accept (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 char* inet_ntop (int const,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
accept_client(int server_fd)
{
	int fd;
	struct sockaddr sa;
	socklen_t sa_len;
	char tmp[INET6_ADDRSTRLEN + 50];
	const char *name;

	sa_len = sizeof sa;
	fd = accept(server_fd, &sa, &sa_len);
	if (fd < 0) {
		perror("accept()");
		return -1;
	}
	name = NULL;
	switch (sa.sa_family) {
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
		sprintf(tmp, "<unknown: %lu>", (unsigned long)sa.sa_family);
		name = tmp;
	}
	fprintf(stderr, "accepting connection from: %s\n", name);
	return fd;
}