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
struct in_addr {int dummy; } ;

/* Variables and functions */
 int INET_ADDRSTRLEN ; 
 int inet_aton (char*,struct in_addr*) ; 
 scalar_t__ isascii (char const) ; 
 scalar_t__ isdigit (char const) ; 
 int /*<<< orphan*/  seterr (struct snmp_client*,char*,...) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static inline const char *
get_ipv4(struct snmp_client *sc, const char **strp)
{
	const char *p = *strp;

	while (isascii(*p) && (isdigit(*p) || *p == '.'))
		p++;

	if (p - *strp > INET_ADDRSTRLEN) {
		seterr(sc, "IPv4 address too long '%.*s'", p - *strp, *strp);
		return (NULL);
	}
	if (*strp == p)
		return *strp;

	char str[INET_ADDRSTRLEN + 1];
	strncpy(str, *strp, p - *strp);
	str[p - *strp] = '\0';

	struct in_addr addr;
	if (inet_aton(str, &addr) != 1) {
		seterr(sc, "illegal IPv4 address '%s'", str);
		return (NULL);
	}

	*strp = p;
	return (p);
}