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
typedef  int /*<<< orphan*/  u_short ;
typedef  int sa_family_t ;
typedef  int /*<<< orphan*/  pbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  pbuf_copy_data (int /*<<< orphan*/ *,int,int,void*) ; 

void *
pf_pull_hdr(pbuf_t *pbuf, int off, void *p, int len,
    u_short *actionp, u_short *reasonp, sa_family_t af)
{
	switch (af) {
#if INET
	case AF_INET: {
		struct ip	*h = pbuf->pb_data;
		u_int16_t	 fragoff = (ntohs(h->ip_off) & IP_OFFMASK) << 3;

		if (fragoff) {
			if (fragoff >= len) {
				ACTION_SET(actionp, PF_PASS);
			} else {
				ACTION_SET(actionp, PF_DROP);
				REASON_SET(reasonp, PFRES_FRAG);
			}
			return (NULL);
		}
		if (pbuf->pb_packet_len < (unsigned)(off + len) ||
		    ntohs(h->ip_len) < off + len) {
			ACTION_SET(actionp, PF_DROP);
			REASON_SET(reasonp, PFRES_SHORT);
			return (NULL);
		}
		break;
	}
#endif /* INET */
#if INET6
	case AF_INET6: {
		struct ip6_hdr	*h = pbuf->pb_data;

		if (pbuf->pb_packet_len < (unsigned)(off + len) ||
		    (ntohs(h->ip6_plen) + sizeof (struct ip6_hdr)) <
		    (unsigned)(off + len)) {
			ACTION_SET(actionp, PF_DROP);
			REASON_SET(reasonp, PFRES_SHORT);
			return (NULL);
		}
		break;
	}
#endif /* INET6 */
	}
	pbuf_copy_data(pbuf, off, len, p);
	return (p);
}