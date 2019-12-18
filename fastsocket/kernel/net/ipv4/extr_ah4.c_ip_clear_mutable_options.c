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
struct iphdr {int ihl; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
#define  IPOPT_CIPSO 134 
#define  IPOPT_END 133 
#define  IPOPT_LSRR 132 
#define  IPOPT_NOOP 131 
#define  IPOPT_RA 130 
#define  IPOPT_SEC 129 
#define  IPOPT_SSRR 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ip_clear_mutable_options(struct iphdr *iph, __be32 *daddr)
{
	unsigned char * optptr = (unsigned char*)(iph+1);
	int  l = iph->ihl*4 - sizeof(struct iphdr);
	int  optlen;

	while (l > 0) {
		switch (*optptr) {
		case IPOPT_END:
			return 0;
		case IPOPT_NOOP:
			l--;
			optptr++;
			continue;
		}
		optlen = optptr[1];
		if (optlen<2 || optlen>l)
			return -EINVAL;
		switch (*optptr) {
		case IPOPT_SEC:
		case 0x85:	/* Some "Extended Security" crap. */
		case IPOPT_CIPSO:
		case IPOPT_RA:
		case 0x80|21:	/* RFC1770 */
			break;
		case IPOPT_LSRR:
		case IPOPT_SSRR:
			if (optlen < 6)
				return -EINVAL;
			memcpy(daddr, optptr+optlen-4, 4);
			/* Fall through */
		default:
			memset(optptr, 0, optlen);
		}
		l -= optlen;
		optptr += optlen;
	}
	return 0;
}