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
typedef  int /*<<< orphan*/  uint64_t ;
struct hostent {char* h_name; } ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_pfargd_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int NS_IN6ADDRSZ ; 
 int /*<<< orphan*/  NS_INADDRSZ ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  bcopy (void const*,char*,size_t) ; 
 int dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*) ; 
 struct hostent* gethostbyaddr_r (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hostent*,char*,int,...) ; 
 struct hostent* getipnodebyaddr (char*,int,int /*<<< orphan*/ ,int*) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

__attribute__((used)) static int
pfprint_inetaddr(dtrace_hdl_t *dtp, FILE *fp, const char *format,
    const dt_pfargd_t *pfd, const void *addr, size_t size, uint64_t normal)
{
	char *s = alloca(size + 1);
	struct hostent *host, res;
	char inetaddr[NS_IN6ADDRSZ];
	char buf[1024];
	int e;

	bcopy(addr, s, size);
	s[size] = '\0';

	if (strchr(s, ':') == NULL && inet_pton(AF_INET, s, inetaddr) != -1) {
#ifdef illumos
		if ((host = gethostbyaddr_r(inetaddr, NS_INADDRSZ,
		    AF_INET, &res, buf, sizeof (buf), &e)) != NULL)
#else
		if (gethostbyaddr_r(inetaddr, NS_INADDRSZ,
		    AF_INET, &res, buf, sizeof (buf), &host, &e) > 0)
#endif
			return (dt_printf(dtp, fp, format, host->h_name));
	} else if (inet_pton(AF_INET6, s, inetaddr) != -1) {
		if ((host = getipnodebyaddr(inetaddr, NS_IN6ADDRSZ,
		    AF_INET6, &e)) != NULL)
			return (dt_printf(dtp, fp, format, host->h_name));
	}

	return (dt_printf(dtp, fp, format, s));
}