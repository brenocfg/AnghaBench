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
struct sockaddr_in6 {unsigned short sin6_port; } ;
struct sockaddr_in {unsigned short sin_port; } ;
struct sockaddr {int sa_family; } ;
struct TCP_Server_Info {int /*<<< orphan*/  dstaddr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  CIFS_PORT ; 
 int /*<<< orphan*/  RFC1001_PORT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned short htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
match_port(struct TCP_Server_Info *server, struct sockaddr *addr)
{
	unsigned short int port, *sport;

	switch (addr->sa_family) {
	case AF_INET:
		sport = &((struct sockaddr_in *) &server->dstaddr)->sin_port;
		port = ((struct sockaddr_in *) addr)->sin_port;
		break;
	case AF_INET6:
		sport = &((struct sockaddr_in6 *) &server->dstaddr)->sin6_port;
		port = ((struct sockaddr_in6 *) addr)->sin6_port;
		break;
	default:
		WARN_ON(1);
		return false;
	}

	if (!port) {
		port = htons(CIFS_PORT);
		if (port == *sport)
			return true;

		port = htons(RFC1001_PORT);
	}

	return port == *sport;
}