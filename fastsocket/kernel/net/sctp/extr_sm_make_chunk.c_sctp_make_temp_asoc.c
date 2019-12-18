#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk; } ;
struct sctp_endpoint {TYPE_2__ base; } ;
struct sctp_chunk {struct sk_buff* skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  peer_addr; } ;
struct sctp_association {int temp; TYPE_1__ c; } ;
struct sctp_af {int /*<<< orphan*/  (* from_skb ) (int /*<<< orphan*/ *,struct sk_buff*,int) ;} ;
typedef  int /*<<< orphan*/  sctp_scope_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipver2af (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_association_free (struct sctp_association*) ; 
 struct sctp_association* sctp_association_new (struct sctp_endpoint const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_af* sctp_get_af_specific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_scope (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_source (struct sctp_chunk*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

struct sctp_association *sctp_make_temp_asoc(const struct sctp_endpoint *ep,
					struct sctp_chunk *chunk,
					gfp_t gfp)
{
	struct sctp_association *asoc;
	struct sk_buff *skb;
	sctp_scope_t scope;
	struct sctp_af *af;

	/* Create the bare association.  */
	scope = sctp_scope(sctp_source(chunk));
	asoc = sctp_association_new(ep, ep->base.sk, scope, gfp);
	if (!asoc)
		goto nodata;
	asoc->temp = 1;
	skb = chunk->skb;
	/* Create an entry for the source address of the packet.  */
	af = sctp_get_af_specific(ipver2af(ip_hdr(skb)->version));
	if (unlikely(!af))
		goto fail;
	af->from_skb(&asoc->c.peer_addr, skb, 1);
nodata:
	return asoc;

fail:
	sctp_association_free(asoc);
	return NULL;
}