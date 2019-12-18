#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct xfrm_user_sec_ctx {int dummy; } ;
struct TYPE_4__ {int dead; } ;
struct TYPE_3__ {void* hard_packet_limit; void* soft_packet_limit; void* hard_byte_limit; void* soft_byte_limit; } ;
struct xfrm_policy {int family; TYPE_2__ walk; int /*<<< orphan*/  security; scalar_t__ xfrm_nr; TYPE_1__ lft; int /*<<< orphan*/  action; } ;
struct sock {int sk_family; } ;
struct sadb_x_sec_ctx {int sadb_x_sec_len; } ;
struct sadb_x_policy {int sadb_x_policy_len; scalar_t__ sadb_x_policy_type; int sadb_x_policy_dir; } ;
struct net {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int EINVAL ; 
 int ENOBUFS ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IPSEC_DIR_OUTBOUND ; 
 scalar_t__ IPSEC_POLICY_BYPASS ; 
 scalar_t__ IPSEC_POLICY_DISCARD ; 
 scalar_t__ IPSEC_POLICY_IPSEC ; 
 int IPV6_IPSEC_POLICY ; 
 int IP_IPSEC_POLICY ; 
 void* XFRM_INF ; 
 int /*<<< orphan*/  XFRM_POLICY_ALLOW ; 
 int /*<<< orphan*/  XFRM_POLICY_BLOCK ; 
 int /*<<< orphan*/  kfree (struct xfrm_user_sec_ctx*) ; 
 int parse_ipsecrequests (struct xfrm_policy*,struct sadb_x_policy*) ; 
 struct xfrm_user_sec_ctx* pfkey_sadb2xfrm_user_sec_ctx (struct sadb_x_sec_ctx*) ; 
 int security_xfrm_policy_alloc (int /*<<< orphan*/ *,struct xfrm_user_sec_ctx*) ; 
 struct net* sock_net (struct sock*) ; 
 int verify_sec_ctx_len (char*) ; 
 struct xfrm_policy* xfrm_policy_alloc (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_policy_destroy (struct xfrm_policy*) ; 

__attribute__((used)) static struct xfrm_policy *pfkey_compile_policy(struct sock *sk, int opt,
						u8 *data, int len, int *dir)
{
	struct net *net = sock_net(sk);
	struct xfrm_policy *xp;
	struct sadb_x_policy *pol = (struct sadb_x_policy*)data;
	struct sadb_x_sec_ctx *sec_ctx;

	switch (sk->sk_family) {
	case AF_INET:
		if (opt != IP_IPSEC_POLICY) {
			*dir = -EOPNOTSUPP;
			return NULL;
		}
		break;
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	case AF_INET6:
		if (opt != IPV6_IPSEC_POLICY) {
			*dir = -EOPNOTSUPP;
			return NULL;
		}
		break;
#endif
	default:
		*dir = -EINVAL;
		return NULL;
	}

	*dir = -EINVAL;

	if (len < sizeof(struct sadb_x_policy) ||
	    pol->sadb_x_policy_len*8 > len ||
	    pol->sadb_x_policy_type > IPSEC_POLICY_BYPASS ||
	    (!pol->sadb_x_policy_dir || pol->sadb_x_policy_dir > IPSEC_DIR_OUTBOUND))
		return NULL;

	xp = xfrm_policy_alloc(net, GFP_ATOMIC);
	if (xp == NULL) {
		*dir = -ENOBUFS;
		return NULL;
	}

	xp->action = (pol->sadb_x_policy_type == IPSEC_POLICY_DISCARD ?
		      XFRM_POLICY_BLOCK : XFRM_POLICY_ALLOW);

	xp->lft.soft_byte_limit = XFRM_INF;
	xp->lft.hard_byte_limit = XFRM_INF;
	xp->lft.soft_packet_limit = XFRM_INF;
	xp->lft.hard_packet_limit = XFRM_INF;
	xp->family = sk->sk_family;

	xp->xfrm_nr = 0;
	if (pol->sadb_x_policy_type == IPSEC_POLICY_IPSEC &&
	    (*dir = parse_ipsecrequests(xp, pol)) < 0)
		goto out;

	/* security context too */
	if (len >= (pol->sadb_x_policy_len*8 +
	    sizeof(struct sadb_x_sec_ctx))) {
		char *p = (char *)pol;
		struct xfrm_user_sec_ctx *uctx;

		p += pol->sadb_x_policy_len*8;
		sec_ctx = (struct sadb_x_sec_ctx *)p;
		if (len < pol->sadb_x_policy_len*8 +
		    sec_ctx->sadb_x_sec_len) {
			*dir = -EINVAL;
			goto out;
		}
		if ((*dir = verify_sec_ctx_len(p)))
			goto out;
		uctx = pfkey_sadb2xfrm_user_sec_ctx(sec_ctx);
		*dir = security_xfrm_policy_alloc(&xp->security, uctx);
		kfree(uctx);

		if (*dir)
			goto out;
	}

	*dir = pol->sadb_x_policy_dir-1;
	return xp;

out:
	xp->walk.dead = 1;
	xfrm_policy_destroy(xp);
	return NULL;
}