#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  scalar_t__ u_int16_t ;
struct udphdr {int dummy; } ;
struct ip6_hdr {int dummy; } ;
struct ip {int dummy; } ;
typedef  int sa_family_t ;
struct TYPE_12__ {int* pb_csum_flags; int* pb_csum_data; unsigned int pb_packet_len; unsigned int pb_contig_len; } ;
typedef  TYPE_1__ pbuf_t ;
struct TYPE_16__ {int /*<<< orphan*/  icps_checksum; } ;
struct TYPE_15__ {int m_len; int m_data; } ;
struct TYPE_14__ {int /*<<< orphan*/  tcps_rcvbadsum; } ;
struct TYPE_13__ {int /*<<< orphan*/  udps_badsum; } ;
struct TYPE_11__ {int /*<<< orphan*/  icp6s_checksum; } ;

/* Variables and functions */
#define  AF_INET 133 
#define  AF_INET6 132 
 int CSUM_DATA_VALID ; 
 int CSUM_PSEUDO_HDR ; 
#define  IPPROTO_ICMP 131 
#define  IPPROTO_ICMPV6 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 TYPE_10__ icmp6stat ; 
 TYPE_9__ icmpstat ; 
 scalar_t__ in_cksum (TYPE_7__*,int) ; 
 TYPE_7__* m ; 
 scalar_t__ pbuf_inet6_cksum (TYPE_1__*,int,int,int) ; 
 scalar_t__ pbuf_inet_cksum (TYPE_1__*,int,int,int) ; 
 TYPE_3__ tcpstat ; 
 TYPE_2__ udpstat ; 

__attribute__((used)) static int
pf_check_proto_cksum(pbuf_t *pbuf, int off, int len, u_int8_t p,
    sa_family_t af)
{
	u_int16_t sum;

	switch (p) {
	case IPPROTO_TCP:
	case IPPROTO_UDP:
		/*
		 * Optimize for the common case; if the hardware calculated
		 * value doesn't include pseudo-header checksum, or if it
		 * is partially-computed (only 16-bit summation), do it in
		 * software below.
		 */
		if ((*pbuf->pb_csum_flags &
		    (CSUM_DATA_VALID | CSUM_PSEUDO_HDR)) ==
		    (CSUM_DATA_VALID | CSUM_PSEUDO_HDR) &&
		    (*pbuf->pb_csum_data ^ 0xffff) == 0) {
			return (0);
		}
		break;
	case IPPROTO_ICMP:
#if INET6
	case IPPROTO_ICMPV6:
#endif /* INET6 */
		break;
	default:
		return (1);
	}
	if (off < (int)sizeof (struct ip) || len < (int)sizeof (struct udphdr))
		return (1);
	if (pbuf->pb_packet_len < (unsigned)(off + len))
		return (1);
	switch (af) {
#if INET
	case AF_INET:
		if (p == IPPROTO_ICMP) {
#if 0
			if (m->m_len < off)
				return (1);
			m->m_data += off;
			m->m_len -= off;
			sum = in_cksum(m, len);
			m->m_data -= off;
			m->m_len += off;
#else
			if (pbuf->pb_contig_len < (unsigned)off)
				return (1);
			sum = pbuf_inet_cksum(pbuf, 0, off, len);
#endif
		} else {
			if (pbuf->pb_contig_len < (int)sizeof (struct ip))
				return (1);
			sum = pbuf_inet_cksum(pbuf, p, off, len);
		}
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		if (pbuf->pb_contig_len < (int)sizeof (struct ip6_hdr))
			return (1);
		sum = pbuf_inet6_cksum(pbuf, p, off, len);
		break;
#endif /* INET6 */
	default:
		return (1);
	}
	if (sum) {
		switch (p) {
		case IPPROTO_TCP:
			tcpstat.tcps_rcvbadsum++;
			break;
		case IPPROTO_UDP:
			udpstat.udps_badsum++;
			break;
		case IPPROTO_ICMP:
			icmpstat.icps_checksum++;
			break;
#if INET6
		case IPPROTO_ICMPV6:
			icmp6stat.icp6s_checksum++;
			break;
#endif /* INET6 */
		}
		return (1);
	}
	return (0);
}