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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  char u_char ;
struct in6_addr {int* s6_addr8; int /*<<< orphan*/ * s6_addr16; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  l ;
typedef  int /*<<< orphan*/  ctxt ;
typedef  struct in6_addr SHA1_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_ADDR_INT16_MLL ; 
 int /*<<< orphan*/  SHA1Final (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  SHA1Init (struct in6_addr*) ; 
 int /*<<< orphan*/  SHA1Update (struct in6_addr*,char*,char) ; 
 int SHA1_RESULTLEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  bzero (struct in6_addr*,int) ; 
 scalar_t__ in6_setscope (struct in6_addr*,struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,char) ; 

int
in6_nigroup(
	struct ifnet *ifp,
	const char *name,
	int namelen,
	struct in6_addr *in6)
{
	const char *p;
	u_char *q;
	SHA1_CTX ctxt;
	u_int8_t digest[SHA1_RESULTLEN];
	char l;
	char n[64];	/* a single label must not exceed 63 chars */

	if (!namelen || !name)
		return (-1);

	p = name;
	while (p && *p && *p != '.' && p - name < namelen)
		p++;
	if (p - name > sizeof (n) - 1)
		return (-1);	/* label too long */
	l = p - name;
	strlcpy(n, name, l);
	n[(int)l] = '\0';
	for (q = (u_char *) n; *q; q++) {
		if ('A' <= *q && *q <= 'Z')
			*q = *q - 'A' + 'a';
	}

	/* generate 16 bytes of pseudo-random value. */
	bzero(&ctxt, sizeof (ctxt));
	SHA1Init(&ctxt);
	SHA1Update(&ctxt, &l, sizeof (l));
	SHA1Update(&ctxt, n, l);
	SHA1Final(digest, &ctxt);

	bzero(in6, sizeof (*in6));
	in6->s6_addr16[0] = IPV6_ADDR_INT16_MLL;
	in6->s6_addr8[11] = 2;
	in6->s6_addr8[12] = 0xff;
	/* copy first 3 bytes of prefix into address */
	bcopy(digest, &in6->s6_addr8[13], 3);
	if (in6_setscope(in6, ifp, NULL))
		return (-1); /* XXX: should not fail */

	return (0);
}