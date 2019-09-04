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
typedef  int u_short ;
typedef  scalar_t__ u_char ;
struct mbuf {int m_len; } ;
struct ip6_hdr {int ip6_nxt; int /*<<< orphan*/  ip6_plen; } ;
struct ip6_fw {scalar_t__ fw_ip6opt; scalar_t__ fw_ip6nopt; } ;
struct ip6_frag {int ip6f_offlg; } ;
struct ip6_ext {int ip6e_nxt; int /*<<< orphan*/  ip6e_len; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int IP6F_OFF_MASK ; 
#define  IPPROTO_AH 134 
#define  IPPROTO_DSTOPTS 133 
#define  IPPROTO_ESP 132 
#define  IPPROTO_FRAGMENT 131 
#define  IPPROTO_HOPOPTS 130 
#define  IPPROTO_NONE 129 
#define  IPPROTO_ROUTING 128 
 scalar_t__ IPV6_FW_IP6OPT_AH ; 
 scalar_t__ IPV6_FW_IP6OPT_ESP ; 
 scalar_t__ IPV6_FW_IP6OPT_FRAG ; 
 scalar_t__ IPV6_FW_IP6OPT_HOPOPT ; 
 scalar_t__ IPV6_FW_IP6OPT_NONXT ; 
 scalar_t__ IPV6_FW_IP6OPT_OPTS ; 
 scalar_t__ IPV6_FW_IP6OPT_ROUTE ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip6opts_match(struct ip6_hdr **pip6, struct ip6_fw *f, struct mbuf **m,
	      int *off, int *nxt, u_short *offset)
{
	int len;
	struct ip6_hdr *ip6 = *pip6;
	struct ip6_ext *ip6e;
	u_char	opts, nopts, nopts_sve;

	opts = f->fw_ip6opt;
	nopts = nopts_sve = f->fw_ip6nopt;

	*nxt = ip6->ip6_nxt;
	*off = sizeof(struct ip6_hdr);
	len = ntohs(ip6->ip6_plen) + sizeof(struct ip6_hdr);
	while (*off < len) {
		ip6e = (struct ip6_ext *)((caddr_t) ip6 + *off);
		if ((*m)->m_len < *off + sizeof(*ip6e))
			goto opts_check;	/* XXX */

		switch(*nxt) {
		case IPPROTO_FRAGMENT:
			if ((*m)->m_len >= *off + sizeof(struct ip6_frag)) {
				struct ip6_frag *ip6f;

				ip6f = (struct ip6_frag *) ((caddr_t)ip6 + *off);
				*offset = ip6f->ip6f_offlg & IP6F_OFF_MASK;
			}
			opts &= ~IPV6_FW_IP6OPT_FRAG;
			nopts &= ~IPV6_FW_IP6OPT_FRAG;
			*off += sizeof(struct ip6_frag);
			break;
		case IPPROTO_AH:
			opts &= ~IPV6_FW_IP6OPT_AH;
			nopts &= ~IPV6_FW_IP6OPT_AH;
			*off += (ip6e->ip6e_len + 2) << 2;
			break;
		default:
			switch (*nxt) {
			case IPPROTO_HOPOPTS:
				opts &= ~IPV6_FW_IP6OPT_HOPOPT;
				nopts &= ~IPV6_FW_IP6OPT_HOPOPT;
				break;
			case IPPROTO_ROUTING:
				opts &= ~IPV6_FW_IP6OPT_ROUTE;
				nopts &= ~IPV6_FW_IP6OPT_ROUTE;
				break;
			case IPPROTO_ESP:
				opts &= ~IPV6_FW_IP6OPT_ESP;
				nopts &= ~IPV6_FW_IP6OPT_ESP;
				break;
			case IPPROTO_NONE:
				opts &= ~IPV6_FW_IP6OPT_NONXT;
				nopts &= ~IPV6_FW_IP6OPT_NONXT;
				goto opts_check;
				break;
			case IPPROTO_DSTOPTS:
				opts &= ~IPV6_FW_IP6OPT_OPTS;
				nopts &= ~IPV6_FW_IP6OPT_OPTS;
				break;
			default:
				goto opts_check;
				break;
			}
			*off += (ip6e->ip6e_len + 1) << 3;
			break;
		}
		*nxt = ip6e->ip6e_nxt;

	}
 opts_check:
	if (f->fw_ip6opt == f->fw_ip6nopt)	/* XXX */
		return 1;

	if (opts == 0 && nopts == nopts_sve)
		return 1;
	else
		return 0;
}