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
struct service {int proto; int /*<<< orphan*/  port; } ;
struct servent {char* s_name; char** s_aliases; char* s_proto; int /*<<< orphan*/  s_port; } ;

/* Variables and functions */
 int ALIGN ; 
#define  EAI_MEMORY 129 
#define  EAI_SYSTEM 128 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ERANGE ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int MAXSERVS ; 
 int __lookup_serv (struct service*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int getservbyname_r(const char *name, const char *prots,
	struct servent *se, char *buf, size_t buflen, struct servent **res)
{
	struct service servs[MAXSERVS];
	int cnt, proto, align;

	/* Align buffer */
	align = -(uintptr_t)buf & ALIGN-1;
	if (buflen < 2*sizeof(char *)+align)
		return ERANGE;
	buf += align;

	if (!prots) proto = 0;
	else if (!strcmp(prots, "tcp")) proto = IPPROTO_TCP;
	else if (!strcmp(prots, "udp")) proto = IPPROTO_UDP;
	else return EINVAL;

	cnt = __lookup_serv(servs, name, proto, 0, 0);
	if (cnt<0) switch (cnt) {
	case EAI_MEMORY:
	case EAI_SYSTEM:
		return ENOMEM;
	default:
		return ENOENT;
	}

	se->s_name = (char *)name;
	se->s_aliases = (void *)buf;
	se->s_aliases[0] = se->s_name;
	se->s_aliases[1] = 0;
	se->s_port = htons(servs[0].port);
	se->s_proto = servs[0].proto == IPPROTO_TCP ? "tcp" : "udp";

	*res = se;
	return 0;
}