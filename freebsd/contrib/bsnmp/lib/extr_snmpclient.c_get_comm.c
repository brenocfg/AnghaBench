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

/* Variables and functions */
 int SNMP_COMMUNITY_MAXLEN ; 
 int /*<<< orphan*/  seterr (struct snmp_client*,char*,int,char const*) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static inline const char *
get_comm(struct snmp_client *sc, const char **strp)
{
	const char *p = strrchr(*strp, '@');

	if (p == NULL)
		/* no community string */
		return (*strp);

	if (p - *strp > SNMP_COMMUNITY_MAXLEN) {
		seterr(sc, "community string too long '%.*s'",
		    p - *strp, *strp);
		return (NULL);
	}

	*strp = p + 1;
	return (p);
}