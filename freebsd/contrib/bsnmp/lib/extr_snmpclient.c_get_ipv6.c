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
struct snmp_client {int dummy; } ;
struct addrinfo {int ai_flags; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int AI_CANONNAME ; 
 int AI_NUMERICHOST ; 
 int IF_NAMESIZE ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seterr (struct snmp_client*,char*,...) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static inline const char *
get_ipv6(struct snmp_client *sc, const char **strp)
{
	char str[INET6_ADDRSTRLEN + IF_NAMESIZE];
	struct addrinfo hints, *res;
	int error;

	if (**strp != '[')
		return (*strp + 1);

	const char *p = *strp + 1;
	while (*p != ']' ) {
		if (*p == '\0') {
			seterr(sc, "unterminated IPv6 address '%.*s'",
			    p - *strp, *strp);
			return (NULL);
		}
		p++;
	}

	if (p - *strp > INET6_ADDRSTRLEN + IF_NAMESIZE) {
		seterr(sc, "IPv6 address too long '%.*s'", p - *strp, *strp);
		return (NULL);
	}

	strncpy(str, *strp + 1, p - (*strp + 1));
	str[p - (*strp + 1)] = '\0';

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_CANONNAME | AI_NUMERICHOST;
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	error = getaddrinfo(str, NULL, &hints, &res);
	if (error != 0) {
		seterr(sc, "%s: %s", str, gai_strerror(error));
		return (NULL);
	}
	freeaddrinfo(res);
	*strp = p + 1;
	return (p);
}