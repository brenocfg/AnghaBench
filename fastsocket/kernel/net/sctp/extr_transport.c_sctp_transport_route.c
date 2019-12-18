#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct sctp_transport {int param_flags; int /*<<< orphan*/  pathmtu; int /*<<< orphan*/  saddr; struct dst_entry* dst; union sctp_addr ipaddr; struct sctp_af* af_specific; struct sctp_association* asoc; } ;
struct sctp_sock {TYPE_3__* pf; } ;
struct TYPE_8__ {int /*<<< orphan*/  sk; } ;
struct TYPE_5__ {struct sctp_transport* active_path; int /*<<< orphan*/  primary_path; } ;
struct sctp_association {TYPE_4__ base; TYPE_1__ peer; } ;
struct sctp_af {int /*<<< orphan*/  (* get_saddr ) (struct sctp_sock*,struct sctp_transport*,union sctp_addr*,struct flowi*) ;struct dst_entry* (* get_dst ) (struct sctp_association*,union sctp_addr*,union sctp_addr*,struct flowi*,int /*<<< orphan*/ ) ;} ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_7__ {TYPE_2__* af; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* to_sk_saddr ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DEFAULT_MAXSEGMENT ; 
 int SPP_PMTUD_DISABLE ; 
 int /*<<< orphan*/  dst_mtu (struct dst_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,union sctp_addr*,int) ; 
 int /*<<< orphan*/  sctp_opt2sk (struct sctp_sock*) ; 
 struct dst_entry* stub1 (struct sctp_association*,union sctp_addr*,union sctp_addr*,struct flowi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct sctp_sock*,struct sctp_transport*,union sctp_addr*,struct flowi*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sctp_transport_route(struct sctp_transport *transport,
			  union sctp_addr *saddr, struct sctp_sock *opt)
{
	struct sctp_association *asoc = transport->asoc;
	struct sctp_af *af = transport->af_specific;
	union sctp_addr *daddr = &transport->ipaddr;
	struct dst_entry *dst;
	struct flowi fl;

	dst = af->get_dst(asoc, daddr, saddr, &fl, sctp_opt2sk(opt));
	transport->dst = dst;

	if (saddr)
		memcpy(&transport->saddr, saddr, sizeof(union sctp_addr));
	else
		af->get_saddr(opt, transport, daddr, &fl);

	if ((transport->param_flags & SPP_PMTUD_DISABLE) && transport->pathmtu) {
		return;
	}
	if (dst) {
		transport->pathmtu = dst_mtu(dst);

		/* Initialize sk->sk_rcv_saddr, if the transport is the
		 * association's active path for getsockname().
		 */
		if (asoc && (!asoc->peer.primary_path ||
				(transport == asoc->peer.active_path)))
			opt->pf->af->to_sk_saddr(&transport->saddr,
						 asoc->base.sk);
	} else
		transport->pathmtu = SCTP_DEFAULT_MAXSEGMENT;
}