#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int16_t ;
struct ip6_hdr {int /*<<< orphan*/  ip6_plen; int /*<<< orphan*/  ip_len; int /*<<< orphan*/  ip_off; } ;
struct ip {int /*<<< orphan*/  ip6_plen; int /*<<< orphan*/  ip_len; int /*<<< orphan*/  ip_off; } ;
typedef  int sa_family_t ;
struct TYPE_4__ {unsigned int pb_packet_len; struct ip6_hdr* pb_data; } ;
typedef  TYPE_1__ pbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  AF_INET 129 
#define  AF_INET6 128 
 int IP_OFFMASK ; 
 int /*<<< orphan*/  PFRES_FRAG ; 
 int /*<<< orphan*/  PFRES_SHORT ; 
 int /*<<< orphan*/  PF_DROP ; 
 int /*<<< orphan*/  PF_PASS ; 
 int /*<<< orphan*/  REASON_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbuf_copy_data (TYPE_1__*,int,int,void*) ; 

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