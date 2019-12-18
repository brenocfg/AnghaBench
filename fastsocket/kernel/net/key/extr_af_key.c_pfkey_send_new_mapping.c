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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  family; int /*<<< orphan*/  saddr; } ;
struct TYPE_5__ {scalar_t__ proto; int /*<<< orphan*/  spi; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq; } ;
struct xfrm_state {TYPE_3__ props; TYPE_2__ id; TYPE_1__ km; struct xfrm_encap_tmpl* encap; } ;
struct xfrm_encap_tmpl {int /*<<< orphan*/  encap_sport; } ;
struct sockaddr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_x_nat_t_port {int sadb_x_nat_t_port_len; scalar_t__ sadb_x_nat_t_port_reserved; int /*<<< orphan*/  sadb_x_nat_t_port_port; int /*<<< orphan*/  sadb_x_nat_t_port_exttype; } ;
struct sadb_sa {int sadb_sa_len; scalar_t__ sadb_sa_flags; scalar_t__ sadb_sa_encrypt; scalar_t__ sadb_sa_auth; scalar_t__ sadb_sa_state; scalar_t__ sadb_sa_replay; int /*<<< orphan*/  sadb_sa_spi; int /*<<< orphan*/  sadb_sa_exttype; } ;
struct sadb_msg {int sadb_msg_len; scalar_t__ sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; scalar_t__ sadb_msg_reserved; scalar_t__ sadb_msg_errno; scalar_t__ sadb_msg_satype; int /*<<< orphan*/  sadb_msg_type; int /*<<< orphan*/  sadb_msg_version; } ;
struct sadb_address {int sadb_address_len; void* sadb_address_prefixlen; scalar_t__ sadb_address_reserved; scalar_t__ sadb_address_proto; int /*<<< orphan*/  sadb_address_exttype; } ;
typedef  scalar_t__ __u8 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_REGISTERED ; 
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPPROTO_ESP ; 
 int /*<<< orphan*/  PF_KEY_V2 ; 
 int /*<<< orphan*/  SADB_EXT_ADDRESS_DST ; 
 int /*<<< orphan*/  SADB_EXT_ADDRESS_SRC ; 
 int /*<<< orphan*/  SADB_EXT_SA ; 
 scalar_t__ SADB_SATYPE_ESP ; 
 int /*<<< orphan*/  SADB_X_EXT_NAT_T_DPORT ; 
 int /*<<< orphan*/  SADB_X_EXT_NAT_T_SPORT ; 
 int /*<<< orphan*/  SADB_X_NAT_T_NEW_MAPPING ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_acqseq () ; 
 int pfkey_broadcast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* pfkey_sockaddr_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int pfkey_sockaddr_size (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int pfkey_send_new_mapping(struct xfrm_state *x, xfrm_address_t *ipaddr, __be16 sport)
{
	struct sk_buff *skb;
	struct sadb_msg *hdr;
	struct sadb_sa *sa;
	struct sadb_address *addr;
	struct sadb_x_nat_t_port *n_port;
	int sockaddr_size;
	int size;
	__u8 satype = (x->id.proto == IPPROTO_ESP ? SADB_SATYPE_ESP : 0);
	struct xfrm_encap_tmpl *natt = NULL;

	sockaddr_size = pfkey_sockaddr_size(x->props.family);
	if (!sockaddr_size)
		return -EINVAL;

	if (!satype)
		return -EINVAL;

	if (!x->encap)
		return -EINVAL;

	natt = x->encap;

	/* Build an SADB_X_NAT_T_NEW_MAPPING message:
	 *
	 * HDR | SA | ADDRESS_SRC (old addr) | NAT_T_SPORT (old port) |
	 * ADDRESS_DST (new addr) | NAT_T_DPORT (new port)
	 */

	size = sizeof(struct sadb_msg) +
		sizeof(struct sadb_sa) +
		(sizeof(struct sadb_address) * 2) +
		(sockaddr_size * 2) +
		(sizeof(struct sadb_x_nat_t_port) * 2);

	skb =  alloc_skb(size + 16, GFP_ATOMIC);
	if (skb == NULL)
		return -ENOMEM;

	hdr = (struct sadb_msg *) skb_put(skb, sizeof(struct sadb_msg));
	hdr->sadb_msg_version = PF_KEY_V2;
	hdr->sadb_msg_type = SADB_X_NAT_T_NEW_MAPPING;
	hdr->sadb_msg_satype = satype;
	hdr->sadb_msg_len = size / sizeof(uint64_t);
	hdr->sadb_msg_errno = 0;
	hdr->sadb_msg_reserved = 0;
	hdr->sadb_msg_seq = x->km.seq = get_acqseq();
	hdr->sadb_msg_pid = 0;

	/* SA */
	sa = (struct sadb_sa *) skb_put(skb, sizeof(struct sadb_sa));
	sa->sadb_sa_len = sizeof(struct sadb_sa)/sizeof(uint64_t);
	sa->sadb_sa_exttype = SADB_EXT_SA;
	sa->sadb_sa_spi = x->id.spi;
	sa->sadb_sa_replay = 0;
	sa->sadb_sa_state = 0;
	sa->sadb_sa_auth = 0;
	sa->sadb_sa_encrypt = 0;
	sa->sadb_sa_flags = 0;

	/* ADDRESS_SRC (old addr) */
	addr = (struct sadb_address*)
		skb_put(skb, sizeof(struct sadb_address)+sockaddr_size);
	addr->sadb_address_len =
		(sizeof(struct sadb_address)+sockaddr_size)/
			sizeof(uint64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_SRC;
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;
	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(&x->props.saddr, 0,
				    (struct sockaddr *) (addr + 1),
				    x->props.family);
	if (!addr->sadb_address_prefixlen)
		BUG();

	/* NAT_T_SPORT (old port) */
	n_port = (struct sadb_x_nat_t_port*) skb_put(skb, sizeof (*n_port));
	n_port->sadb_x_nat_t_port_len = sizeof(*n_port)/sizeof(uint64_t);
	n_port->sadb_x_nat_t_port_exttype = SADB_X_EXT_NAT_T_SPORT;
	n_port->sadb_x_nat_t_port_port = natt->encap_sport;
	n_port->sadb_x_nat_t_port_reserved = 0;

	/* ADDRESS_DST (new addr) */
	addr = (struct sadb_address*)
		skb_put(skb, sizeof(struct sadb_address)+sockaddr_size);
	addr->sadb_address_len =
		(sizeof(struct sadb_address)+sockaddr_size)/
			sizeof(uint64_t);
	addr->sadb_address_exttype = SADB_EXT_ADDRESS_DST;
	addr->sadb_address_proto = 0;
	addr->sadb_address_reserved = 0;
	addr->sadb_address_prefixlen =
		pfkey_sockaddr_fill(ipaddr, 0,
				    (struct sockaddr *) (addr + 1),
				    x->props.family);
	if (!addr->sadb_address_prefixlen)
		BUG();

	/* NAT_T_DPORT (new port) */
	n_port = (struct sadb_x_nat_t_port*) skb_put(skb, sizeof (*n_port));
	n_port->sadb_x_nat_t_port_len = sizeof(*n_port)/sizeof(uint64_t);
	n_port->sadb_x_nat_t_port_exttype = SADB_X_EXT_NAT_T_DPORT;
	n_port->sadb_x_nat_t_port_port = sport;
	n_port->sadb_x_nat_t_port_reserved = 0;

	return pfkey_broadcast(skb, GFP_ATOMIC, BROADCAST_REGISTERED, NULL, xs_net(x));
}