#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfrm_policy {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_x_policy {int /*<<< orphan*/  sadb_x_policy_id; } ;
struct sadb_msg {scalar_t__ sadb_msg_type; int /*<<< orphan*/  sadb_msg_pid; int /*<<< orphan*/  sadb_msg_seq; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int byid; } ;
struct km_event {int /*<<< orphan*/  event; TYPE_1__ data; int /*<<< orphan*/  pid; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_MARK ; 
 int EINVAL ; 
 int ENOENT ; 
 int SADB_X_EXT_POLICY ; 
 scalar_t__ SADB_X_SPDDELETE2 ; 
 int /*<<< orphan*/  XFRM_MSG_DELPOLICY ; 
 unsigned int XFRM_POLICY_MAX ; 
 int /*<<< orphan*/  XFRM_POLICY_TYPE_MAIN ; 
 int /*<<< orphan*/  audit_get_loginuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_get_sessionid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int key_pol_get_resp (struct sock*,struct xfrm_policy*,struct sadb_msg*,unsigned int) ; 
 int /*<<< orphan*/  km_policy_notify (struct xfrm_policy*,unsigned int,struct km_event*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  xfrm_audit_policy_delete (struct xfrm_policy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_pol_put (struct xfrm_policy*) ; 
 struct xfrm_policy* xfrm_policy_byid (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int*) ; 
 unsigned int xfrm_policy_id2dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pfkey_spdget(struct sock *sk, struct sk_buff *skb, struct sadb_msg *hdr, void **ext_hdrs)
{
	struct net *net = sock_net(sk);
	unsigned int dir;
	int err = 0, delete;
	struct sadb_x_policy *pol;
	struct xfrm_policy *xp;
	struct km_event c;

	if ((pol = ext_hdrs[SADB_X_EXT_POLICY-1]) == NULL)
		return -EINVAL;

	dir = xfrm_policy_id2dir(pol->sadb_x_policy_id);
	if (dir >= XFRM_POLICY_MAX)
		return -EINVAL;

	delete = (hdr->sadb_msg_type == SADB_X_SPDDELETE2);
	xp = xfrm_policy_byid(net, DUMMY_MARK, XFRM_POLICY_TYPE_MAIN,
			      dir, pol->sadb_x_policy_id, delete, &err);
	if (xp == NULL)
		return -ENOENT;

	if (delete) {
		xfrm_audit_policy_delete(xp, err ? 0 : 1,
				audit_get_loginuid(current),
				audit_get_sessionid(current), 0);

		if (err)
			goto out;
		c.seq = hdr->sadb_msg_seq;
		c.pid = hdr->sadb_msg_pid;
		c.data.byid = 1;
		c.event = XFRM_MSG_DELPOLICY;
		km_policy_notify(xp, dir, &c);
	} else {
		err = key_pol_get_resp(sk, xp, hdr, dir);
	}

out:
	xfrm_pol_put(xp);
	return err;
}