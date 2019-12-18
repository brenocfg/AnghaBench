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
typedef  int u_char ;
struct ip {int /*<<< orphan*/  ip_vhl; } ;

/* Variables and functions */
 scalar_t__ IPOPT_COPIED (int) ; 
 int IPOPT_EOL ; 
 int IPOPT_NOP ; 
 int IPOPT_OLEN ; 
 int IP_VHL_HL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int*,int*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
ip_optcopy(struct ip *ip, struct ip *jp)
{
	u_char *cp, *dp;
	int opt, optlen, cnt;

	cp = (u_char *)(ip + 1);
	dp = (u_char *)(jp + 1);
	cnt = (IP_VHL_HL(ip->ip_vhl) << 2) - sizeof (struct ip);
	for (; cnt > 0; cnt -= optlen, cp += optlen) {
		opt = cp[0];
		if (opt == IPOPT_EOL)
			break;
		if (opt == IPOPT_NOP) {
			/* Preserve for IP mcast tunnel's LSRR alignment. */
			*dp++ = IPOPT_NOP;
			optlen = 1;
			continue;
		}
#if DIAGNOSTIC
		if (cnt < IPOPT_OLEN + sizeof (*cp)) {
			panic("malformed IPv4 option passed to ip_optcopy");
			/* NOTREACHED */
		}
#endif
		optlen = cp[IPOPT_OLEN];
#if DIAGNOSTIC
		if (optlen < IPOPT_OLEN + sizeof (*cp) || optlen > cnt) {
			panic("malformed IPv4 option passed to ip_optcopy");
			/* NOTREACHED */
		}
#endif
		/* bogus lengths should have been caught by ip_dooptions */
		if (optlen > cnt)
			optlen = cnt;
		if (IPOPT_COPIED(opt)) {
			bcopy(cp, dp, optlen);
			dp += optlen;
		}
	}
	for (optlen = dp - (u_char *)(jp+1); optlen & 0x3; optlen++)
		*dp++ = IPOPT_EOL;
	return (optlen);
}