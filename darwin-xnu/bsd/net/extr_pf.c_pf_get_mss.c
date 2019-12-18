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
typedef  int u_int8_t ;
typedef  int u_int16_t ;
struct tcphdr {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  pbuf_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NTOHS (int) ; 
 int TCPOLEN_MAXSEG ; 
#define  TCPOPT_EOL 130 
#define  TCPOPT_MAXSEG 129 
#define  TCPOPT_NOP 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pf_pull_hdr (int /*<<< orphan*/ *,int,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tcp_mssdflt ; 

__attribute__((used)) static u_int16_t
pf_get_mss(pbuf_t *pbuf, int off, u_int16_t th_off, sa_family_t af)
{
	int		 hlen;
	u_int8_t	 hdr[60];
	u_int8_t	*opt, optlen;
	u_int16_t	 mss = tcp_mssdflt;

	hlen = th_off << 2;	/* hlen <= sizeof (hdr) */
	if (hlen <= (int)sizeof (struct tcphdr))
		return (0);
	if (!pf_pull_hdr(pbuf, off, hdr, hlen, NULL, NULL, af))
		return (0);
	opt = hdr + sizeof (struct tcphdr);
	hlen -= sizeof (struct tcphdr);
	while (hlen >= TCPOLEN_MAXSEG) {
		switch (*opt) {
		case TCPOPT_EOL:
		case TCPOPT_NOP:
			++opt;
			--hlen;
			break;
		case TCPOPT_MAXSEG:
			bcopy((caddr_t)(opt + 2), (caddr_t)&mss, 2);
#if BYTE_ORDER != BIG_ENDIAN
			NTOHS(mss);
#endif
			/* FALLTHROUGH */
		default:
			optlen = opt[1];
			if (optlen < 2)
				optlen = 2;
			hlen -= optlen;
			opt += optlen;
			break;
		}
	}
	return (mss);
}