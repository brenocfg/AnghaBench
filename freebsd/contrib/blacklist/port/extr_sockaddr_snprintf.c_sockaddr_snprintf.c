#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_un {int /*<<< orphan*/  sun_path; } ;
struct sockaddr_in6 {int sin6_flowinfo; int sin6_scope_id; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr_dl {int dummy; } ;
struct netrange {int nr_phase; int nr_firstnet; int nr_lastnet; } ;
struct TYPE_3__ {struct netrange r_netrange; } ;
struct TYPE_4__ {int s_node; int /*<<< orphan*/  s_net; } ;
struct sockaddr_at {TYPE_1__ sat_range; TYPE_2__ sat_addr; int /*<<< orphan*/  sat_port; } ;
struct sockaddr {int sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  pbuf ;
typedef  int /*<<< orphan*/  nbuf ;
typedef  int /*<<< orphan*/  abuf ;

/* Variables and functions */
 int /*<<< orphan*/  ADDC (char const) ; 
 int /*<<< orphan*/  ADDNA () ; 
 int /*<<< orphan*/  ADDS (char*) ; 
#define  AF_APPLETALK 133 
#define  AF_INET 132 
#define  AF_INET6 131 
#define  AF_LINK 130 
#define  AF_LOCAL 129 
#define  AF_UNSPEC 128 
 int /*<<< orphan*/  EAFNOSUPPORT ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int SLEN (struct sockaddr const* const) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  debug_at (char*,int,struct sockaddr_at const*) ; 
 int /*<<< orphan*/  debug_dl (char*,int,struct sockaddr_dl const*) ; 
 int /*<<< orphan*/  debug_in (char*,int,struct sockaddr_in const*) ; 
 int /*<<< orphan*/  debug_in6 (char*,int,struct sockaddr_in6 const*) ; 
 int /*<<< orphan*/  debug_un (char*,int,struct sockaddr_un const*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getnameinfo (struct sockaddr const* const,int /*<<< orphan*/ ,char*,unsigned int,char*,unsigned int,int) ; 
 int /*<<< orphan*/  link_ntoa (struct sockaddr_dl const*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

int
sockaddr_snprintf(char * const sbuf, const size_t len, const char * const fmt,
    const struct sockaddr * const sa)
{
	const void *a = NULL;
	char abuf[1024], nbuf[1024], *addr = NULL;

	char Abuf[1024], pbuf[32], *name = NULL, *port = NULL;
	char *ebuf = &sbuf[len - 1], *buf = sbuf;
	const char *ptr, *s;
	int p = -1;
#ifdef HAVE_NETATALK_AT_H
	const struct sockaddr_at *sat = NULL;
#endif
	const struct sockaddr_in *sin4 = NULL;
	const struct sockaddr_in6 *sin6 = NULL;
	const struct sockaddr_un *sun = NULL;
#ifdef HAVE_NET_IF_DL_H
	const struct sockaddr_dl *sdl = NULL;
	char *w = NULL;
#endif
	int na = 1;

#define ADDC(c) do { if (buf < ebuf) *buf++ = c; else buf++; } \
	while (/*CONSTCOND*/0)
#define ADDS(p) do { for (s = p; *s; s++) ADDC(*s); } \
	while (/*CONSTCOND*/0)
#define ADDNA() do { if (na) ADDS("N/A"); } \
	while (/*CONSTCOND*/0)

	switch (sa->sa_family) {
	case AF_UNSPEC:
		goto done;
#ifdef HAVE_NETATALK_AT_H
	case AF_APPLETALK:
		sat = ((const struct sockaddr_at *)(const void *)sa);
		p = ntohs(sat->sat_port);
		(void)snprintf(addr = abuf, sizeof(abuf), "%u.%u",
			ntohs(sat->sat_addr.s_net), sat->sat_addr.s_node);
		(void)snprintf(port = pbuf, sizeof(pbuf), "%d", p);
		break;
#endif
	case AF_LOCAL:
		sun = ((const struct sockaddr_un *)(const void *)sa);
		(void)strlcpy(addr = abuf, sun->sun_path, sizeof(abuf));
		break;
	case AF_INET:
		sin4 = ((const struct sockaddr_in *)(const void *)sa);
		p = ntohs(sin4->sin_port);
		a = &sin4->sin_addr;
		break;
	case AF_INET6:
		sin6 = ((const struct sockaddr_in6 *)(const void *)sa);
		p = ntohs(sin6->sin6_port);
		a = &sin6->sin6_addr;
		break;
#ifdef HAVE_NET_IF_DL_H
	case AF_LINK:
		sdl = ((const struct sockaddr_dl *)(const void *)sa);
		(void)strlcpy(addr = abuf, link_ntoa(sdl), sizeof(abuf));
		if ((w = strchr(addr, ':')) != NULL) {
			*w++ = '\0';
			addr = w;
		}
		break;
#endif
	default:
		errno = EAFNOSUPPORT;
		return -1;
	}

	if (addr == abuf)
		name = addr;

	if (a && getnameinfo(sa, (socklen_t)SLEN(sa), addr = abuf,
	    (unsigned int)sizeof(abuf), NULL, 0,
	    NI_NUMERICHOST|NI_NUMERICSERV) != 0)
		return -1;

	for (ptr = fmt; *ptr; ptr++) {
		if (*ptr != '%') {
			ADDC(*ptr);
			continue;
		}
	  next_char:
		switch (*++ptr) {
		case '?':
			na = 0;
			goto next_char;
		case 'a':
			ADDS(addr);
			break;
		case 'p':
			if (p != -1) {
				(void)snprintf(nbuf, sizeof(nbuf), "%d", p);
				ADDS(nbuf);
			} else
				ADDNA();
			break;
		case 'f':
			(void)snprintf(nbuf, sizeof(nbuf), "%d", sa->sa_family);
			ADDS(nbuf);
			break;
		case 'l':
			(void)snprintf(nbuf, sizeof(nbuf), "%d", SLEN(sa));
			ADDS(nbuf);
			break;
		case 'A':
			if (name)
				ADDS(name);
			else if (!a)
				ADDNA();
			else {
				getnameinfo(sa, (socklen_t)SLEN(sa),
					name = Abuf,
					(unsigned int)sizeof(nbuf), NULL, 0, 0);
				ADDS(name);
			}
			break;
		case 'P':
			if (port)
				ADDS(port);
			else if (p == -1)
				ADDNA();
			else {
				getnameinfo(sa, (socklen_t)SLEN(sa), NULL, 0,
					port = pbuf,
					(unsigned int)sizeof(pbuf), 0);
				ADDS(port);
			}
			break;
		case 'I':
#ifdef HAVE_NET_IF_DL_H
			if (sdl && addr != abuf) {
				ADDS(abuf);
			} else
#endif
			{
				ADDNA();
			}
			break;
		case 'F':
			if (sin6) {
				(void)snprintf(nbuf, sizeof(nbuf), "%d",
				    sin6->sin6_flowinfo);
				ADDS(nbuf);
				break;
			} else {
				ADDNA();
			}
			break;
		case 'S':
			if (sin6) {
				(void)snprintf(nbuf, sizeof(nbuf), "%d",
				    sin6->sin6_scope_id);
				ADDS(nbuf);
				break;
			} else {
				ADDNA();
			}
			break;
		case 'R':
#ifdef HAVE_NETATALK_AT_H
			if (sat) {
				const struct netrange *n =
				    &sat->sat_range.r_netrange;
				(void)snprintf(nbuf, sizeof(nbuf),
				    "%d:[%d,%d]", n->nr_phase , n->nr_firstnet,
				    n->nr_lastnet);
				ADDS(nbuf);
			} else
#endif
			{
				ADDNA();
			}
			break;
		case 'D':
			switch (sa->sa_family) {
#ifdef HAVE_NETATALK_AT_H
			case AF_APPLETALK:
				debug_at(nbuf, sizeof(nbuf), sat);
				break;
#endif
			case AF_LOCAL:
				debug_un(nbuf, sizeof(nbuf), sun);
				break;
			case AF_INET:
				debug_in(nbuf, sizeof(nbuf), sin4);
				break;
			case AF_INET6:
				debug_in6(nbuf, sizeof(nbuf), sin6);
				break;
#ifdef HAVE_NET_IF_DL_H
			case AF_LINK:
				debug_dl(nbuf, sizeof(nbuf), sdl);
				break;
#endif
			default:
				abort();
			}
			ADDS(nbuf);
			break;
		default:
			ADDC('%');
			if (na == 0)
				ADDC('?');
			if (*ptr == '\0')
				goto done;
			/*FALLTHROUGH*/
		case '%':
			ADDC(*ptr);
			break;
		}
		na = 1;
	}
done:
	if (buf < ebuf)
		*buf = '\0';
	else if (len != 0)
		sbuf[len - 1] = '\0';
	return (int)(buf - sbuf);
}