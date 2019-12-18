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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct nf_conn {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 unsigned int SIP_PORT ; 
 int /*<<< orphan*/  htons (unsigned int) ; 
 int /*<<< orphan*/  parse_addr (struct nf_conn const*,char const*,char const**,union nf_inet_addr*,char const*) ; 
 unsigned int simple_strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  skp_epaddr_len (struct nf_conn const*,char const*,char const*,int*) ; 
 unsigned int string_len (struct nf_conn const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strnicmp (char const*,char*,int /*<<< orphan*/ ) ; 

int ct_sip_parse_request(const struct nf_conn *ct,
			 const char *dptr, unsigned int datalen,
			 unsigned int *matchoff, unsigned int *matchlen,
			 union nf_inet_addr *addr, __be16 *port)
{
	const char *start = dptr, *limit = dptr + datalen, *end;
	unsigned int mlen;
	unsigned int p;
	int shift = 0;

	/* Skip method and following whitespace */
	mlen = string_len(ct, dptr, limit, NULL);
	if (!mlen)
		return 0;
	dptr += mlen;
	if (++dptr >= limit)
		return 0;

	/* Find SIP URI */
	limit -= strlen("sip:");
	for (; dptr < limit; dptr++) {
		if (*dptr == '\r' || *dptr == '\n')
			return -1;
		if (strnicmp(dptr, "sip:", strlen("sip:")) == 0)
			break;
	}
	if (!skp_epaddr_len(ct, dptr, limit, &shift))
		return 0;
	dptr += shift;

	if (!parse_addr(ct, dptr, &end, addr, limit))
		return -1;
	if (end < limit && *end == ':') {
		end++;
		p = simple_strtoul(end, (char **)&end, 10);
		if (p < 1024 || p > 65535)
			return -1;
		*port = htons(p);
	} else
		*port = htons(SIP_PORT);

	if (end == dptr)
		return 0;
	*matchoff = dptr - start;
	*matchlen = end - dptr;
	return 1;
}