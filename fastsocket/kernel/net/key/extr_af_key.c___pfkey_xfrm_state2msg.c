#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  reqid; int /*<<< orphan*/  mode; int /*<<< orphan*/  family; int /*<<< orphan*/  saddr; int /*<<< orphan*/  replay_window; } ;
struct TYPE_18__ {int /*<<< orphan*/  sport; int /*<<< orphan*/  saddr; void* prefixlen_s; int /*<<< orphan*/  proto; } ;
struct TYPE_17__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  spi; } ;
struct TYPE_16__ {int /*<<< orphan*/  use_time; int /*<<< orphan*/  add_time; void* bytes; void* packets; } ;
struct TYPE_15__ {int /*<<< orphan*/  soft_use_expires_seconds; int /*<<< orphan*/  soft_add_expires_seconds; int /*<<< orphan*/  soft_byte_limit; int /*<<< orphan*/  soft_packet_limit; int /*<<< orphan*/  hard_use_expires_seconds; int /*<<< orphan*/  hard_add_expires_seconds; int /*<<< orphan*/  hard_byte_limit; int /*<<< orphan*/  hard_packet_limit; } ;
struct TYPE_12__ {int state; int /*<<< orphan*/  dying; } ;
struct xfrm_state {TYPE_10__ props; TYPE_9__* ealg; TYPE_8__* aalg; TYPE_7__ sel; TYPE_6__ id; TYPE_5__ curlft; TYPE_4__ lft; TYPE_2__* calg; TYPE_1__ km; struct xfrm_encap_tmpl* encap; struct xfrm_sec_ctx* security; } ;
struct xfrm_sec_ctx {int ctx_len; int /*<<< orphan*/  ctx_str; int /*<<< orphan*/  ctx_alg; int /*<<< orphan*/  ctx_doi; } ;
struct xfrm_encap_tmpl {int /*<<< orphan*/  encap_dport; int /*<<< orphan*/  encap_sport; scalar_t__ encap_type; } ;
struct TYPE_14__ {scalar_t__ sadb_alg_id; } ;
struct xfrm_algo_desc {TYPE_3__ desc; } ;
struct sockaddr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_x_sec_ctx {int sadb_key_len; int sadb_key_bits; int sadb_x_sec_len; int sadb_x_ctx_len; int /*<<< orphan*/  sadb_x_ctx_alg; int /*<<< orphan*/  sadb_x_ctx_doi; int /*<<< orphan*/  sadb_x_sec_exttype; scalar_t__ sadb_key_reserved; int /*<<< orphan*/  sadb_key_exttype; } ;
struct sadb_x_sa2 {int sadb_x_sa2_len; int sadb_x_sa2_mode; int /*<<< orphan*/  sadb_x_sa2_reqid; scalar_t__ sadb_x_sa2_sequence; scalar_t__ sadb_x_sa2_reserved2; scalar_t__ sadb_x_sa2_reserved1; int /*<<< orphan*/  sadb_x_sa2_exttype; } ;
struct sadb_x_nat_t_type {int sadb_x_nat_t_type_len; scalar_t__* sadb_x_nat_t_type_reserved; scalar_t__ sadb_x_nat_t_type_type; int /*<<< orphan*/  sadb_x_nat_t_type_exttype; } ;
struct sadb_x_nat_t_port {int sadb_x_nat_t_port_len; scalar_t__ sadb_x_nat_t_port_reserved; int /*<<< orphan*/  sadb_x_nat_t_port_port; int /*<<< orphan*/  sadb_x_nat_t_port_exttype; } ;
struct sadb_sa {int sadb_sa_len; int /*<<< orphan*/  sadb_sa_flags; scalar_t__ sadb_sa_encrypt; scalar_t__ sadb_sa_auth; int /*<<< orphan*/  sadb_sa_state; int /*<<< orphan*/  sadb_sa_replay; int /*<<< orphan*/  sadb_sa_spi; int /*<<< orphan*/  sadb_sa_exttype; } ;
struct sadb_msg {int sadb_msg_len; } ;
struct sadb_lifetime {int sadb_lifetime_len; int /*<<< orphan*/  sadb_lifetime_usetime; int /*<<< orphan*/  sadb_lifetime_addtime; void* sadb_lifetime_bytes; void* sadb_lifetime_allocations; int /*<<< orphan*/  sadb_lifetime_exttype; } ;
struct sadb_key {int sadb_key_len; int sadb_key_bits; int sadb_x_sec_len; int sadb_x_ctx_len; int /*<<< orphan*/  sadb_x_ctx_alg; int /*<<< orphan*/  sadb_x_ctx_doi; int /*<<< orphan*/  sadb_x_sec_exttype; scalar_t__ sadb_key_reserved; int /*<<< orphan*/  sadb_key_exttype; } ;
struct sadb_address {int sadb_address_len; scalar_t__ sadb_address_reserved; void* sadb_address_prefixlen; scalar_t__ sadb_address_proto; int /*<<< orphan*/  sadb_address_exttype; } ;
struct TYPE_20__ {int alg_key_len; int /*<<< orphan*/  alg_key; int /*<<< orphan*/  alg_name; } ;
struct TYPE_19__ {int alg_key_len; int /*<<< orphan*/  alg_key; int /*<<< orphan*/  alg_name; } ;
struct TYPE_13__ {int /*<<< orphan*/  alg_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOBUFS ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PFKEY_ALIGN8 (int) ; 
 int /*<<< orphan*/  SADB_EXT_ADDRESS_DST ; 
 int /*<<< orphan*/  SADB_EXT_ADDRESS_PROXY ; 
 int /*<<< orphan*/  SADB_EXT_ADDRESS_SRC ; 
 int /*<<< orphan*/  SADB_EXT_KEY_AUTH ; 
 int /*<<< orphan*/  SADB_EXT_KEY_ENCRYPT ; 
 int /*<<< orphan*/  SADB_EXT_LIFETIME_CURRENT ; 
 int /*<<< orphan*/  SADB_EXT_LIFETIME_HARD ; 
 int /*<<< orphan*/  SADB_EXT_LIFETIME_SOFT ; 
 int /*<<< orphan*/  SADB_EXT_SA ; 
 int /*<<< orphan*/  SADB_SAFLAGS_DECAP_DSCP ; 
 int /*<<< orphan*/  SADB_SAFLAGS_NOECN ; 
 int /*<<< orphan*/  SADB_SAFLAGS_NOPMTUDISC ; 
 int /*<<< orphan*/  SADB_SASTATE_DEAD ; 
 int /*<<< orphan*/  SADB_SASTATE_DYING ; 
 int /*<<< orphan*/  SADB_SASTATE_LARVAL ; 
 int /*<<< orphan*/  SADB_SASTATE_MATURE ; 
 int /*<<< orphan*/  SADB_X_EXT_NAT_T_DPORT ; 
 int /*<<< orphan*/  SADB_X_EXT_NAT_T_SPORT ; 
 int /*<<< orphan*/  SADB_X_EXT_NAT_T_TYPE ; 
 int /*<<< orphan*/  SADB_X_EXT_SA2 ; 
 int /*<<< orphan*/  SADB_X_EXT_SEC_CTX ; 
#define  XFRM_STATE_ACQ 129 
 int XFRM_STATE_DECAP_DSCP ; 
 int XFRM_STATE_NOECN ; 
 int XFRM_STATE_NOPMTUDISC ; 
#define  XFRM_STATE_VALID 128 
 void* _X2KEY (int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct sadb_x_sec_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sadb_msg*,int /*<<< orphan*/ ,int) ; 
 int pfkey_mode_from_xfrm (int /*<<< orphan*/ ) ; 
 scalar_t__ pfkey_proto_from_xfrm (int /*<<< orphan*/ ) ; 
 void* pfkey_sockaddr_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int pfkey_sockaddr_size (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 struct xfrm_algo_desc* xfrm_aalg_get_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xfrm_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xfrm_algo_desc* xfrm_calg_get_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfrm_algo_desc* xfrm_ealg_get_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *__pfkey_xfrm_state2msg(struct xfrm_state *x,
					      int add_keys, int hsc)
{
	struct sk_buff *skb;
	struct sadb_msg *hdr;
	struct sadb_sa *sa;
	struct sadb_lifetime *lifetime;
	struct sadb_address *addr;
	struct sadb_key *key;
	struct sadb_x_sa2 *sa2;
	struct sadb_x_sec_ctx *sec_ctx;
	struct xfrm_sec_ctx *xfrm_ctx;
	int ctx_size = 0;
	int size;
	int auth_key_size = 0;
	int encrypt_key_size = 0;
	int sockaddr_size;
	struct xfrm_encap_tmpl *natt = NULL;
	int mode;

	/* address family check */
	sockaddr_size = pfkey_sockaddr_size(x->props.family);
	if (!sockaddr_size)
		return ERR_PTR(-EINVAL);

	/* base, SA, (lifetime (HSC),) address(SD), (address(P),)
	   key(AE), (identity(SD),) (sensitivity)> */
	size = sizeof(struct sadb_msg) +sizeof(struct sadb_sa) +
		sizeof(struct sadb_lifetime) +
		((hsc & 1) ? sizeof(struct sadb_lifetime) : 0) +
		((hsc & 2) ? sizeof(struct sadb_lifetime) : 0) +
			sizeof(struct sadb_address)*2 +
				sockaddr_size*2 +
					sizeof(struct sadb_x_sa2);

	if ((xfrm_ctx = x->security)) {
		ctx_size = PFKEY_ALIGN8(xfrm_ctx->ctx_len);
		size += sizeof(struct sadb_x_sec_ctx) + ctx_size;
	}

	/* identity & sensitivity */
	if (xfrm_addr_cmp(&x->sel.saddr, &x->props.saddr, x->props.family))
		size += sizeof(struct sadb_address) + sockaddr_size;

	if (add_keys) {
		if (x->aalg && x->aalg->alg_key_len) {
			auth_key_size =
				PFKEY_ALIGN8((x->aalg->alg_key_len + 7) / 8);
			size += sizeof(struct sadb_key) + auth_key_size;
		}
		if (x->ealg && x->ealg->alg_key_len) {
			encrypt_key_size =
				PFKEY_ALIGN8((x->ealg->alg_key_len+7) / 8);
			size += sizeof(struct sadb_key) + encrypt_key_size;
		}
	}
	if (x->encap)
		natt = x->encap;

	if (natt && natt->encap_type) {
		size += sizeof(struct sadb_x_nat_t_type);
		size += sizeof(struct sadb_x_nat_t_port);
		size += sizeof(struct sadb_x_nat_t_port);
	}

	skb =  alloc_skb(size + 16, GFP_ATOMIC);
	if (skb == NULL)
		return ERR_PTR(-ENOBUFS);

	/* call should fill header later */
	hdr = (struct sadb_msg *) skb_put(skb, sizeof(struct sadb_msg));
	memset(hdr, 0, size);	/* XXX do we need this ? */
	hdr->sadb_msg_len = size / sizeof(uint64_t);

	/* sa */
	sa = (struct sadb_sa *)  skb_put(skb, sizeof(struct sadb_sa));
	sa->sadb_sa_len = sizeof(struct sadb_sa)/sizeof(uint64_t);
	sa->sadb_sa_exttype = SADB_EXT_SA;
	sa->sadb_sa_spi = x->id.spi;
	sa->sadb_sa_replay = x->props.replay_window;
	switch (x->km.state) {
	case XFRM_STATE_VALID:
		sa->sadb_sa_state = x->km.dying ?
			SADB_SASTATE_DYING : SADB_SASTATE_MATURE;
		break;
	case XFRM_STATE_ACQ:
		sa->sadb_sa_state = SADB_SASTATE_LARVAL;
		break;
	default:
		sa->sadb_sa_state = SADB_SASTATE_DEAD;
		break;
	}
	sa->sadb_sa_auth = 0;
	if (x->aalg) {
		struct xfrm_algo_desc *a = xfrm_aalg_get_byname(x->aalg->alg_name, 0);
		sa->sadb_sa_auth = a ? a->desc.sadb_alg_id : 0;
	}
	sa->sadb_sa_encrypt = 0;
	BUG_ON(x->ealg && x->calg);
	if (x->ealg) {
		struct xfrm_algo_desc *a = xfrm_ealg_get_byname(x->ealg->alg_name, 0);
		sa->sadb_sa_encrypt = a ? a->desc.sadb_alg_id : 0;
	}
	/* KAME compatible: sadb_sa_encrypt is overloaded with calg id */
	if (x->calg) {
		struct xfrm_algo_desc *a = xfrm_calg_get_byname(x->calg->alg_name, 0);
		sa->sadb_sa_encrypt = a ? a->desc.sadb_alg_id : 0;
	}

	sa->sadb_sa_flags = 0;
	if (x->props.flags & XFRM_STATE_NOECN)
		sa->sadb_sa_flags |= SADB_SAFLAGS_NOECN;
	if (x->props.flags & XFRM_STATE_DECAP_DSCP)
		sa->sadb_sa_flags |= SADB_SAFLAGS_DECAP_DSCP;
	if (x->props.flags & XFRM_STATE_NOPMTUDISC)
		sa->sadb_sa_flags |= SADB_SAFLAGS_NOPMTUDISC;

	/* hard time */
	if (hsc & 2) {
		lifetime = (struct sadb_lifetime *)  skb_put(skb,
							     sizeof(struct sadb_lifetime));
		lifetime->sadb_lifetime_len =
			sizeof(struct sadb_lifetime)/sizeof(uint64_t);
		lifetime->sadb_lifetime_exttype = SADB_EXT_LIFETIME_HARD;
		lifetime->sadb_lifetime_allocations =  _X2KEY(x->lft.hard_packet_limit);
		lifetime->sadb_lifetime_bytes = _X2KEY(x->lft.hard_byte_limit);
		lifetime->sadb_lifetime_addtime = x->lft.hard_add_expires_seconds;
		lifetime->sadb_lifetime_usetime = x->lft.hard_use_expires_seconds;
	}
	/* soft time */
	if (hsc & 1) {
		lifetime = (struct sadb_lifetime *)  skb_put(skb,
							     sizeof(struct sadb_lifetime));
		lifetime->sadb_lifetime_len =
			sizeof(struct sadb_lifetime)/sizeof(uint64_t);
		lifetime->sadb_lifetime_exttype = SADB_EXT_LIFETIME_SOFT;
		lifetime->sadb_lifetime_allocations =  _X2KEY(x->lft.soft_packet_limit);
		lifetime->sadb_lifetime_bytes = _X2KEY(x->lft.soft_byte_limit);
		lifetime->sadb_lifetime_addtime = x->lft.soft_add_expires_seconds;
		lifetime->sadb_lifetime_usetime = x->lft.soft_use_expires_seconds;
	}
	/* current time */
	lifetime = (struct sadb_lifetime *)  skb_put(skb,
						     sizeof(struct sadb_lifetime));
	lifetime->sadb_lifetime_len =
		sizeof(struct sadb_lifetime)/sizeof(uint64_t);
	lifetime->sadb_lifetime_exttype = SADB_EXT_LIFETIME_CURRENT;
	lifetime->sadb_lifetime_allocations = x->curlft.packets;
	lifetime->sadb_lifetime_bytes = x->curlft.bytes;
	lifetime->sadb_lifetime_addtime = x->curlft.add_time;
	lifetime->sadb_lifetime_usetime = x->curlft.use_time;
	/* src address */
	addr = (struct sadb_address*) skb_put(skb,
					      sizeof(struct sadb_address)+sockaddr_size);
	addr->sadb_address_len =
		(sizeof(struct sadb_address)+sockaddr_size)/
			sizeof(uint64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_SRC;
	/* "if the ports are non-zero, then the sadb_address_proto field,
	   normally zero, MUST be filled in with the transport
	   protocol's number." - RFC2367 */
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;

	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(&x->props.saddr, 0,
				    (struct sockaddr *) (addr + 1),
				    x->props.family);
	if (!addr->sadb_address_prefixlen)
		BUG();

	/* dst address */
	addr = (struct sadb_address*) skb_put(skb,
					      sizeof(struct sadb_address)+sockaddr_size);
	addr->sadb_address_len =
		(sizeof(struct sadb_address)+sockaddr_size)/
			sizeof(uint64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_DST;
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;

	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(&x->id.daddr, 0,
				    (struct sockaddr *) (addr + 1),
				    x->props.family);
	if (!addr->sadb_address_prefixlen)
		BUG();

	if (xfrm_addr_cmp(&x->sel.saddr, &x->props.saddr,
			  x->props.family)) {
		addr = (struct sadb_address*) skb_put(skb,
			sizeof(struct sadb_address)+sockaddr_size);
		addr->sadb_address_len =
			(sizeof(struct sadb_address)+sockaddr_size)/
			sizeof(uint64_t);
		addr->sadb_address_exttype = SADB_EXT_ADDRESS_PROXY;
		addr->sadb_address_proto =
			pfkey_proto_from_xfrm(x->sel.proto);
		addr->sadb_address_prefixlen = x->sel.prefixlen_s;
		addr->sadb_address_reserved = 0;

		pfkey_sockaddr_fill(&x->sel.saddr, x->sel.sport,
				    (struct sockaddr *) (addr + 1),
				    x->props.family);
	}

	/* auth key */
	if (add_keys && auth_key_size) {
		key = (struct sadb_key *) skb_put(skb,
						  sizeof(struct sadb_key)+auth_key_size);
		key->sadb_key_len = (sizeof(struct sadb_key) + auth_key_size) /
			sizeof(uint64_t);
		key->sadb_key_exttype = SADB_EXT_KEY_AUTH;
		key->sadb_key_bits = x->aalg->alg_key_len;
		key->sadb_key_reserved = 0;
		memcpy(key + 1, x->aalg->alg_key, (x->aalg->alg_key_len+7)/8);
	}
	/* encrypt key */
	if (add_keys && encrypt_key_size) {
		key = (struct sadb_key *) skb_put(skb,
						  sizeof(struct sadb_key)+encrypt_key_size);
		key->sadb_key_len = (sizeof(struct sadb_key) +
				     encrypt_key_size) / sizeof(uint64_t);
		key->sadb_key_exttype = SADB_EXT_KEY_ENCRYPT;
		key->sadb_key_bits = x->ealg->alg_key_len;
		key->sadb_key_reserved = 0;
		memcpy(key + 1, x->ealg->alg_key,
		       (x->ealg->alg_key_len+7)/8);
	}

	/* sa */
	sa2 = (struct sadb_x_sa2 *)  skb_put(skb, sizeof(struct sadb_x_sa2));
	sa2->sadb_x_sa2_len = sizeof(struct sadb_x_sa2)/sizeof(uint64_t);
	sa2->sadb_x_sa2_exttype = SADB_X_EXT_SA2;
	if ((mode = pfkey_mode_from_xfrm(x->props.mode)) < 0) {
		kfree_skb(skb);
		return ERR_PTR(-EINVAL);
	}
	sa2->sadb_x_sa2_mode = mode;
	sa2->sadb_x_sa2_reserved1 = 0;
	sa2->sadb_x_sa2_reserved2 = 0;
	sa2->sadb_x_sa2_sequence = 0;
	sa2->sadb_x_sa2_reqid = x->props.reqid;

	if (natt && natt->encap_type) {
		struct sadb_x_nat_t_type *n_type;
		struct sadb_x_nat_t_port *n_port;

		/* type */
		n_type = (struct sadb_x_nat_t_type*) skb_put(skb, sizeof(*n_type));
		n_type->sadb_x_nat_t_type_len = sizeof(*n_type)/sizeof(uint64_t);
		n_type->sadb_x_nat_t_type_exttype = SADB_X_EXT_NAT_T_TYPE;
		n_type->sadb_x_nat_t_type_type = natt->encap_type;
		n_type->sadb_x_nat_t_type_reserved[0] = 0;
		n_type->sadb_x_nat_t_type_reserved[1] = 0;
		n_type->sadb_x_nat_t_type_reserved[2] = 0;

		/* source port */
		n_port = (struct sadb_x_nat_t_port*) skb_put(skb, sizeof (*n_port));
		n_port->sadb_x_nat_t_port_len = sizeof(*n_port)/sizeof(uint64_t);
		n_port->sadb_x_nat_t_port_exttype = SADB_X_EXT_NAT_T_SPORT;
		n_port->sadb_x_nat_t_port_port = natt->encap_sport;
		n_port->sadb_x_nat_t_port_reserved = 0;

		/* dest port */
		n_port = (struct sadb_x_nat_t_port*) skb_put(skb, sizeof (*n_port));
		n_port->sadb_x_nat_t_port_len = sizeof(*n_port)/sizeof(uint64_t);
		n_port->sadb_x_nat_t_port_exttype = SADB_X_EXT_NAT_T_DPORT;
		n_port->sadb_x_nat_t_port_port = natt->encap_dport;
		n_port->sadb_x_nat_t_port_reserved = 0;
	}

	/* security context */
	if (xfrm_ctx) {
		sec_ctx = (struct sadb_x_sec_ctx *) skb_put(skb,
				sizeof(struct sadb_x_sec_ctx) + ctx_size);
		sec_ctx->sadb_x_sec_len =
		  (sizeof(struct sadb_x_sec_ctx) + ctx_size) / sizeof(uint64_t);
		sec_ctx->sadb_x_sec_exttype = SADB_X_EXT_SEC_CTX;
		sec_ctx->sadb_x_ctx_doi = xfrm_ctx->ctx_doi;
		sec_ctx->sadb_x_ctx_alg = xfrm_ctx->ctx_alg;
		sec_ctx->sadb_x_ctx_len = xfrm_ctx->ctx_len;
		memcpy(sec_ctx + 1, xfrm_ctx->ctx_str,
		       xfrm_ctx->ctx_len);
	}

	return skb;
}