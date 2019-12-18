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
struct nf_conn {int dummy; } ;

/* Variables and functions */
 char* ct_sip_header_search (char const*,char const*,char const*,int /*<<< orphan*/ ) ; 
 unsigned int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int ct_sip_parse_numerical_param(const struct nf_conn *ct, const char *dptr,
				 unsigned int dataoff, unsigned int datalen,
				 const char *name,
				 unsigned int *matchoff, unsigned int *matchlen,
				 unsigned int *val)
{
	const char *limit = dptr + datalen;
	const char *start;
	char *end;

	limit = ct_sip_header_search(dptr + dataoff, limit, ",", strlen(","));
	if (!limit)
		limit = dptr + datalen;

	start = ct_sip_header_search(dptr + dataoff, limit, name, strlen(name));
	if (!start)
		return 0;

	start += strlen(name);
	*val = simple_strtoul(start, &end, 0);
	if (start == end)
		return 0;
	if (matchoff && matchlen) {
		*matchoff = start - dptr;
		*matchlen = end - start;
	}
	return 1;
}