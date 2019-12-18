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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  proto; } ;
struct xfrm_tmpl {scalar_t__ mode; int /*<<< orphan*/  encap_family; TYPE_3__ id; int /*<<< orphan*/  saddr; scalar_t__ reqid; scalar_t__ optional; } ;
struct xfrm_sec_ctx {int /*<<< orphan*/  ctx_len; int /*<<< orphan*/  ctx_str; int /*<<< orphan*/  ctx_alg; int /*<<< orphan*/  ctx_doi; } ;
struct TYPE_6__ {int /*<<< orphan*/  use_time; int /*<<< orphan*/  add_time; void* bytes; void* packets; } ;
struct TYPE_5__ {int /*<<< orphan*/  soft_use_expires_seconds; int /*<<< orphan*/  soft_add_expires_seconds; int /*<<< orphan*/  soft_byte_limit; int /*<<< orphan*/  soft_packet_limit; int /*<<< orphan*/  hard_use_expires_seconds; int /*<<< orphan*/  hard_add_expires_seconds; int /*<<< orphan*/  hard_byte_limit; int /*<<< orphan*/  hard_packet_limit; } ;
struct TYPE_8__ {int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/  prefixlen_d; int /*<<< orphan*/  proto; int /*<<< orphan*/  sport; int /*<<< orphan*/  saddr; int /*<<< orphan*/  prefixlen_s; } ;
struct xfrm_policy {scalar_t__ action; int xfrm_nr; int /*<<< orphan*/  refcnt; struct xfrm_sec_ctx* security; struct xfrm_tmpl* xfrm_vec; int /*<<< orphan*/  priority; int /*<<< orphan*/  index; TYPE_2__ curlft; TYPE_1__ lft; int /*<<< orphan*/  family; TYPE_4__ selector; } ;
struct sockaddr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_x_sec_ctx {int sadb_x_sec_len; int /*<<< orphan*/  sadb_x_ctx_len; int /*<<< orphan*/  sadb_x_ctx_alg; int /*<<< orphan*/  sadb_x_ctx_doi; int /*<<< orphan*/  sadb_x_sec_exttype; } ;
struct sadb_x_policy {int sadb_x_policy_len; int sadb_x_policy_dir; int /*<<< orphan*/  sadb_x_policy_priority; int /*<<< orphan*/  sadb_x_policy_id; int /*<<< orphan*/  sadb_x_policy_type; int /*<<< orphan*/  sadb_x_policy_exttype; } ;
struct sadb_x_ipsecrequest {int sadb_x_ipsecrequest_len; int sadb_x_ipsecrequest_mode; int sadb_msg_len; int /*<<< orphan*/  sadb_msg_reserved; scalar_t__ sadb_x_ipsecrequest_reqid; int /*<<< orphan*/  sadb_x_ipsecrequest_level; int /*<<< orphan*/  sadb_x_ipsecrequest_proto; } ;
struct sadb_msg {int sadb_x_ipsecrequest_len; int sadb_x_ipsecrequest_mode; int sadb_msg_len; int /*<<< orphan*/  sadb_msg_reserved; scalar_t__ sadb_x_ipsecrequest_reqid; int /*<<< orphan*/  sadb_x_ipsecrequest_level; int /*<<< orphan*/  sadb_x_ipsecrequest_proto; } ;
struct sadb_lifetime {int sadb_lifetime_len; int /*<<< orphan*/  sadb_lifetime_usetime; int /*<<< orphan*/  sadb_lifetime_addtime; void* sadb_lifetime_bytes; void* sadb_lifetime_allocations; int /*<<< orphan*/  sadb_lifetime_exttype; } ;
struct sadb_address {int sadb_address_len; scalar_t__ sadb_address_reserved; int /*<<< orphan*/  sadb_address_prefixlen; void* sadb_address_proto; int /*<<< orphan*/  sadb_address_exttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int /*<<< orphan*/  IPSEC_LEVEL_REQUIRE ; 
 int /*<<< orphan*/  IPSEC_LEVEL_UNIQUE ; 
 int /*<<< orphan*/  IPSEC_LEVEL_USE ; 
 int /*<<< orphan*/  IPSEC_POLICY_DISCARD ; 
 int /*<<< orphan*/  IPSEC_POLICY_IPSEC ; 
 int /*<<< orphan*/  IPSEC_POLICY_NONE ; 
 int /*<<< orphan*/  SADB_EXT_ADDRESS_DST ; 
 int /*<<< orphan*/  SADB_EXT_ADDRESS_SRC ; 
 int /*<<< orphan*/  SADB_EXT_LIFETIME_CURRENT ; 
 int /*<<< orphan*/  SADB_EXT_LIFETIME_HARD ; 
 int /*<<< orphan*/  SADB_EXT_LIFETIME_SOFT ; 
 int /*<<< orphan*/  SADB_X_EXT_POLICY ; 
 int /*<<< orphan*/  SADB_X_EXT_SEC_CTX ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 scalar_t__ XFRM_POLICY_ALLOW ; 
 void* _X2KEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct sadb_x_sec_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sadb_x_ipsecrequest*,int /*<<< orphan*/ ,int) ; 
 int pfkey_mode_from_xfrm (scalar_t__) ; 
 void* pfkey_proto_from_xfrm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_sockaddr_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int pfkey_sockaddr_len (int /*<<< orphan*/ ) ; 
 int pfkey_sockaddr_size (int /*<<< orphan*/ ) ; 
 int pfkey_xfrm_policy2msg_size (struct xfrm_policy*) ; 
 int pfkey_xfrm_policy2sec_ctx_size (struct xfrm_policy*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int pfkey_xfrm_policy2msg(struct sk_buff *skb, struct xfrm_policy *xp, int dir)
{
	struct sadb_msg *hdr;
	struct sadb_address *addr;
	struct sadb_lifetime *lifetime;
	struct sadb_x_policy *pol;
	struct sadb_x_sec_ctx *sec_ctx;
	struct xfrm_sec_ctx *xfrm_ctx;
	int i;
	int size;
	int sockaddr_size = pfkey_sockaddr_size(xp->family);
	int socklen = pfkey_sockaddr_len(xp->family);

	size = pfkey_xfrm_policy2msg_size(xp);

	/* call should fill header later */
	hdr = (struct sadb_msg *) skb_put(skb, sizeof(struct sadb_msg));
	memset(hdr, 0, size);	/* XXX do we need this ? */

	/* src address */
	addr = (struct sadb_address*) skb_put(skb,
					      sizeof(struct sadb_address)+sockaddr_size);
	addr->sadb_address_len =
		(sizeof(struct sadb_address)+sockaddr_size)/
			sizeof(uint64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_SRC;
	addr->sadb_address_proto = pfkey_proto_from_xfrm(xp->selector.proto);
	addr->sadb_address_prefixlen = xp->selector.prefixlen_s;
	addr->sadb_address_reserved = 0;
	if (!pfkey_sockaddr_fill(&xp->selector.saddr,
				 xp->selector.sport,
				 (struct sockaddr *) (addr + 1),
				 xp->family))
		BUG();

	/* dst address */
	addr = (struct sadb_address*) skb_put(skb,
					      sizeof(struct sadb_address)+sockaddr_size);
	addr->sadb_address_len =
		(sizeof(struct sadb_address)+sockaddr_size)/
			sizeof(uint64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_DST;
	addr->sadb_address_proto = pfkey_proto_from_xfrm(xp->selector.proto);
	addr->sadb_address_prefixlen = xp->selector.prefixlen_d;
	addr->sadb_address_reserved = 0;

	pfkey_sockaddr_fill(&xp->selector.daddr, xp->selector.dport,
			    (struct sockaddr *) (addr + 1),
			    xp->family);

	/* hard time */
	lifetime = (struct sadb_lifetime *)  skb_put(skb,
						     sizeof(struct sadb_lifetime));
	lifetime->sadb_lifetime_len =
		sizeof(struct sadb_lifetime)/sizeof(uint64_t);
	lifetime->sadb_lifetime_exttype = SADB_EXT_LIFETIME_HARD;
	lifetime->sadb_lifetime_allocations =  _X2KEY(xp->lft.hard_packet_limit);
	lifetime->sadb_lifetime_bytes = _X2KEY(xp->lft.hard_byte_limit);
	lifetime->sadb_lifetime_addtime = xp->lft.hard_add_expires_seconds;
	lifetime->sadb_lifetime_usetime = xp->lft.hard_use_expires_seconds;
	/* soft time */
	lifetime = (struct sadb_lifetime *)  skb_put(skb,
						     sizeof(struct sadb_lifetime));
	lifetime->sadb_lifetime_len =
		sizeof(struct sadb_lifetime)/sizeof(uint64_t);
	lifetime->sadb_lifetime_exttype = SADB_EXT_LIFETIME_SOFT;
	lifetime->sadb_lifetime_allocations =  _X2KEY(xp->lft.soft_packet_limit);
	lifetime->sadb_lifetime_bytes = _X2KEY(xp->lft.soft_byte_limit);
	lifetime->sadb_lifetime_addtime = xp->lft.soft_add_expires_seconds;
	lifetime->sadb_lifetime_usetime = xp->lft.soft_use_expires_seconds;
	/* current time */
	lifetime = (struct sadb_lifetime *)  skb_put(skb,
						     sizeof(struct sadb_lifetime));
	lifetime->sadb_lifetime_len =
		sizeof(struct sadb_lifetime)/sizeof(uint64_t);
	lifetime->sadb_lifetime_exttype = SADB_EXT_LIFETIME_CURRENT;
	lifetime->sadb_lifetime_allocations = xp->curlft.packets;
	lifetime->sadb_lifetime_bytes = xp->curlft.bytes;
	lifetime->sadb_lifetime_addtime = xp->curlft.add_time;
	lifetime->sadb_lifetime_usetime = xp->curlft.use_time;

	pol = (struct sadb_x_policy *)  skb_put(skb, sizeof(struct sadb_x_policy));
	pol->sadb_x_policy_len = sizeof(struct sadb_x_policy)/sizeof(uint64_t);
	pol->sadb_x_policy_exttype = SADB_X_EXT_POLICY;
	pol->sadb_x_policy_type = IPSEC_POLICY_DISCARD;
	if (xp->action == XFRM_POLICY_ALLOW) {
		if (xp->xfrm_nr)
			pol->sadb_x_policy_type = IPSEC_POLICY_IPSEC;
		else
			pol->sadb_x_policy_type = IPSEC_POLICY_NONE;
	}
	pol->sadb_x_policy_dir = dir+1;
	pol->sadb_x_policy_id = xp->index;
	pol->sadb_x_policy_priority = xp->priority;

	for (i=0; i<xp->xfrm_nr; i++) {
		struct sadb_x_ipsecrequest *rq;
		struct xfrm_tmpl *t = xp->xfrm_vec + i;
		int req_size;
		int mode;

		req_size = sizeof(struct sadb_x_ipsecrequest);
		if (t->mode == XFRM_MODE_TUNNEL) {
			socklen = pfkey_sockaddr_len(t->encap_family);
			req_size += socklen * 2;
		} else {
			size -= 2*socklen;
		}
		rq = (void*)skb_put(skb, req_size);
		pol->sadb_x_policy_len += req_size/8;
		memset(rq, 0, sizeof(*rq));
		rq->sadb_x_ipsecrequest_len = req_size;
		rq->sadb_x_ipsecrequest_proto = t->id.proto;
		if ((mode = pfkey_mode_from_xfrm(t->mode)) < 0)
			return -EINVAL;
		rq->sadb_x_ipsecrequest_mode = mode;
		rq->sadb_x_ipsecrequest_level = IPSEC_LEVEL_REQUIRE;
		if (t->reqid)
			rq->sadb_x_ipsecrequest_level = IPSEC_LEVEL_UNIQUE;
		if (t->optional)
			rq->sadb_x_ipsecrequest_level = IPSEC_LEVEL_USE;
		rq->sadb_x_ipsecrequest_reqid = t->reqid;

		if (t->mode == XFRM_MODE_TUNNEL) {
			u8 *sa = (void *)(rq + 1);
			pfkey_sockaddr_fill(&t->saddr, 0,
					    (struct sockaddr *)sa,
					    t->encap_family);
			pfkey_sockaddr_fill(&t->id.daddr, 0,
					    (struct sockaddr *) (sa + socklen),
					    t->encap_family);
		}
	}

	/* security context */
	if ((xfrm_ctx = xp->security)) {
		int ctx_size = pfkey_xfrm_policy2sec_ctx_size(xp);

		sec_ctx = (struct sadb_x_sec_ctx *) skb_put(skb, ctx_size);
		sec_ctx->sadb_x_sec_len = ctx_size / sizeof(uint64_t);
		sec_ctx->sadb_x_sec_exttype = SADB_X_EXT_SEC_CTX;
		sec_ctx->sadb_x_ctx_doi = xfrm_ctx->ctx_doi;
		sec_ctx->sadb_x_ctx_alg = xfrm_ctx->ctx_alg;
		sec_ctx->sadb_x_ctx_len = xfrm_ctx->ctx_len;
		memcpy(sec_ctx + 1, xfrm_ctx->ctx_str,
		       xfrm_ctx->ctx_len);
	}

	hdr->sadb_msg_len = size / sizeof(uint64_t);
	hdr->sadb_msg_reserved = atomic_read(&xp->refcnt);

	return 0;
}