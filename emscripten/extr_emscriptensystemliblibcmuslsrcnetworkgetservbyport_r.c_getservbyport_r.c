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
struct sockaddr_in {int sin_port; int /*<<< orphan*/  sin_family; } ;
struct servent {int s_port; char* s_proto; char** s_aliases; char* s_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
#define  EAI_MEMORY 129 
#define  EAI_SYSTEM 128 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  NI_DGRAM ; 
 int getnameinfo (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int getservbyport_r(int port, const char *prots,
	struct servent *se, char *buf, size_t buflen, struct servent **res)
{
	int i;
	struct sockaddr_in sin = {
		.sin_family = AF_INET,
		.sin_port = port,
	};

	if (!prots) {
		int r = getservbyport_r(port, "tcp", se, buf, buflen, res);
		if (r) r = getservbyport_r(port, "udp", se, buf, buflen, res);
		return r;
	}

	/* Align buffer */
	i = (uintptr_t)buf & sizeof(char *)-1;
	if (!i) i = sizeof(char *);
	if (buflen < 3*sizeof(char *)-i)
		return ERANGE;
	buf += sizeof(char *)-i;
	buflen -= sizeof(char *)-i;

	if (strcmp(prots, "tcp") && strcmp(prots, "udp")) return EINVAL;

	se->s_port = port;
	se->s_proto = (char *)prots;
	se->s_aliases = (void *)buf;
	buf += 2*sizeof(char *);
	buflen -= 2*sizeof(char *);
	se->s_aliases[1] = 0;
	se->s_aliases[0] = se->s_name = buf;

	switch (getnameinfo((void *)&sin, sizeof sin, 0, 0, buf, buflen,
		strcmp(prots, "udp") ? 0 : NI_DGRAM)) {
	case EAI_MEMORY:
	case EAI_SYSTEM:
		return ENOMEM;
	default:
		return ENOENT;
	case 0:
		break;
	}

	*res = se;
	return 0;
}