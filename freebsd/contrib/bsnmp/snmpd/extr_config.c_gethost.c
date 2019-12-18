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
typedef  int u_char ;
struct TYPE_2__ {int s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct addrinfo {scalar_t__ ai_addr; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  report (char*,char const*,...) ; 

__attribute__((used)) static void
gethost(const char *host, u_char *ip)
{
	struct addrinfo hints, *res;
	int error;
	struct sockaddr_in *sain;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_PASSIVE;
	error = getaddrinfo(host, NULL, &hints, &res);
	if (error != 0)
		report("%s: %s", host, gai_strerror(error));
	if (res == NULL)
		report("%s: unknown hostname", host);

	sain = (struct sockaddr_in *)(void *)res->ai_addr;
	sain->sin_addr.s_addr = ntohl(sain->sin_addr.s_addr);
	ip[0] = sain->sin_addr.s_addr >> 24;
	ip[1] = sain->sin_addr.s_addr >> 16;
	ip[2] = sain->sin_addr.s_addr >>  8;
	ip[3] = sain->sin_addr.s_addr >>  0;

	freeaddrinfo(res);
}