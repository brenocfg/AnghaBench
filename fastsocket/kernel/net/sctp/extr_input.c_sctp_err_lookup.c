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
struct sock {int dummy; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct sctphdr {int /*<<< orphan*/  vtag; } ;
struct sctp_transport {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  init_tag; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct sctp_init_chunk {TYPE_3__ init_hdr; TYPE_2__ chunk_hdr; } ;
struct TYPE_8__ {scalar_t__ my_vtag; scalar_t__ peer_vtag; } ;
struct TYPE_5__ {struct sock* sk; } ;
struct sctp_association {TYPE_4__ c; TYPE_1__ base; } ;
struct sctp_af {int /*<<< orphan*/  (* from_skb ) (union sctp_addr*,struct sk_buff*,int) ;} ;
typedef  int /*<<< orphan*/  sctp_chunkhdr_t ;
typedef  scalar_t__ __u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_LOCKDROPPEDICMPS ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_CID_INIT ; 
 struct sctp_association* __sctp_lookup_association (union sctp_addr*,union sctp_addr*,struct sctp_transport**) ; 
 int /*<<< orphan*/  init_net ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_association_put (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_bh_lock_sock (struct sock*) ; 
 struct sctp_af* sctp_get_af_specific (int) ; 
 scalar_t__ sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  stub1 (union sctp_addr*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub2 (union sctp_addr*,struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

struct sock *sctp_err_lookup(int family, struct sk_buff *skb,
			     struct sctphdr *sctphdr,
			     struct sctp_association **app,
			     struct sctp_transport **tpp)
{
	union sctp_addr saddr;
	union sctp_addr daddr;
	struct sctp_af *af;
	struct sock *sk = NULL;
	struct sctp_association *asoc;
	struct sctp_transport *transport = NULL;
	struct sctp_init_chunk *chunkhdr;
	__u32 vtag = ntohl(sctphdr->vtag);
	int len = skb->len - ((void *)sctphdr - (void *)skb->data);

	*app = NULL; *tpp = NULL;

	af = sctp_get_af_specific(family);
	if (unlikely(!af)) {
		return NULL;
	}

	/* Initialize local addresses for lookups. */
	af->from_skb(&saddr, skb, 1);
	af->from_skb(&daddr, skb, 0);

	/* Look for an association that matches the incoming ICMP error
	 * packet.
	 */
	asoc = __sctp_lookup_association(&saddr, &daddr, &transport);
	if (!asoc)
		return NULL;

	sk = asoc->base.sk;

	/* RFC 4960, Appendix C. ICMP Handling
	 *
	 * ICMP6) An implementation MUST validate that the Verification Tag
	 * contained in the ICMP message matches the Verification Tag of
	 * the peer.  If the Verification Tag is not 0 and does NOT
	 * match, discard the ICMP message.  If it is 0 and the ICMP
	 * message contains enough bytes to verify that the chunk type is
	 * an INIT chunk and that the Initiate Tag matches the tag of the
	 * peer, continue with ICMP7.  If the ICMP message is too short
	 * or the chunk type or the Initiate Tag does not match, silently
	 * discard the packet.
	 */
	if (vtag == 0) {
		chunkhdr = (struct sctp_init_chunk *)((void *)sctphdr
				+ sizeof(struct sctphdr));
		if (len < sizeof(struct sctphdr) + sizeof(sctp_chunkhdr_t)
			  + sizeof(__be32) ||
		    chunkhdr->chunk_hdr.type != SCTP_CID_INIT ||
		    ntohl(chunkhdr->init_hdr.init_tag) != asoc->c.my_vtag) {
			goto out;
		}
	} else if (vtag != asoc->c.peer_vtag) {
		goto out;
	}

	sctp_bh_lock_sock(sk);

	/* If too many ICMPs get dropped on busy
	 * servers this needs to be solved differently.
	 */
	if (sock_owned_by_user(sk))
		NET_INC_STATS_BH(&init_net, LINUX_MIB_LOCKDROPPEDICMPS);

	*app = asoc;
	*tpp = transport;
	return sk;

out:
	if (asoc)
		sctp_association_put(asoc);
	return NULL;
}