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
struct sockaddr_in6 {unsigned int sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
typedef  int socklen_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EAI_FAMILY ; 
 int EAI_NONAME ; 
 int EAI_OVERFLOW ; 
 int /*<<< orphan*/  IF_NAMESIZE ; 
 scalar_t__ IN6_IS_ADDR_LINKLOCAL (unsigned char*) ; 
 scalar_t__ IN6_IS_ADDR_MC_LINKLOCAL (unsigned char*) ; 
 int NI_DGRAM ; 
 int NI_NAMEREQD ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSCOPE ; 
 int NI_NUMERICSERV ; 
 int PTR_MAX ; 
 int /*<<< orphan*/  RR_PTR ; 
 int /*<<< orphan*/  __dns_parse (unsigned char*,int,int /*<<< orphan*/ ,char*) ; 
 int __res_mkquery (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int __res_send (unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  dns_parse_callback ; 
 char* if_indextoname (unsigned int,char*) ; 
 int /*<<< orphan*/  inet_ntop (int,unsigned char*,char*,int) ; 
 char* itoa (char*,int) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  mkptr4 (char*,unsigned char*) ; 
 int /*<<< orphan*/  mkptr6 (char*,unsigned char*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reverse_hosts (char*,unsigned char*,unsigned int,int) ; 
 int /*<<< orphan*/  reverse_services (char*,int,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int getnameinfo(const struct sockaddr *restrict sa, socklen_t sl,
	char *restrict node, socklen_t nodelen,
	char *restrict serv, socklen_t servlen,
	int flags)
{
	char ptr[PTR_MAX];
	char buf[256], num[3*sizeof(int)+1];
	int af = sa->sa_family;
	unsigned char *a;
	unsigned scopeid;

	switch (af) {
	case AF_INET:
		a = (void *)&((struct sockaddr_in *)sa)->sin_addr;
		if (sl < sizeof(struct sockaddr_in)) return EAI_FAMILY;
		mkptr4(ptr, a);
		scopeid = 0;
		break;
	case AF_INET6:
		a = (void *)&((struct sockaddr_in6 *)sa)->sin6_addr;
		if (sl < sizeof(struct sockaddr_in6)) return EAI_FAMILY;
		if (memcmp(a, "\0\0\0\0\0\0\0\0\0\0\xff\xff", 12))
			mkptr6(ptr, a);
		else
			mkptr4(ptr, a+12);
		scopeid = ((struct sockaddr_in6 *)sa)->sin6_scope_id;
		break;
	default:
		return EAI_FAMILY;
	}

	if (node && nodelen) {
		buf[0] = 0;
		if (!(flags & NI_NUMERICHOST)) {
			reverse_hosts(buf, a, scopeid, af);
		}
		if (!*buf && !(flags & NI_NUMERICHOST)) {
			unsigned char query[18+PTR_MAX], reply[512];
			int qlen = __res_mkquery(0, ptr, 1, RR_PTR,
				0, 0, 0, query, sizeof query);
			int rlen = __res_send(query, qlen, reply, sizeof reply);
			buf[0] = 0;
			if (rlen > 0)
				__dns_parse(reply, rlen, dns_parse_callback, buf);
		}
		if (!*buf) {
			if (flags & NI_NAMEREQD) return EAI_NONAME;
			inet_ntop(af, a, buf, sizeof buf);
			if (scopeid) {
				char *p = 0, tmp[IF_NAMESIZE+1];
				if (!(flags & NI_NUMERICSCOPE) &&
				    (IN6_IS_ADDR_LINKLOCAL(a) ||
				     IN6_IS_ADDR_MC_LINKLOCAL(a)))
					p = if_indextoname(scopeid, tmp+1);
				if (!p)
					p = itoa(num, scopeid);
				*--p = '%';
				strcat(buf, p);
			}
		}
		if (strlen(buf) >= nodelen) return EAI_OVERFLOW;
		strcpy(node, buf);
	}

	if (serv && servlen) {
		char *p = buf;
		int port = ntohs(((struct sockaddr_in *)sa)->sin_port);
		buf[0] = 0;
		if (!(flags & NI_NUMERICSERV))
			reverse_services(buf, port, flags & NI_DGRAM);
		if (!*p)
			p = itoa(num, port);
		if (strlen(p) >= servlen)
			return EAI_OVERFLOW;
		strcpy(serv, p);
	}

	return 0;
}