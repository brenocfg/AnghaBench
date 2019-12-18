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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct sadb_msg {int sadb_msg_len; scalar_t__ sadb_msg_errno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ONE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ERESTARTNOHAND ; 
 int ERESTARTNOINTR ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_broadcast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfkey_hdr_dup (struct sadb_msg*,struct sadb_msg*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int pfkey_error(struct sadb_msg *orig, int err, struct sock *sk)
{
	struct sk_buff *skb = alloc_skb(sizeof(struct sadb_msg) + 16, GFP_KERNEL);
	struct sadb_msg *hdr;

	if (!skb)
		return -ENOBUFS;

	/* Woe be to the platform trying to support PFKEY yet
	 * having normal errnos outside the 1-255 range, inclusive.
	 */
	err = -err;
	if (err == ERESTARTSYS ||
	    err == ERESTARTNOHAND ||
	    err == ERESTARTNOINTR)
		err = EINTR;
	if (err >= 512)
		err = EINVAL;
	BUG_ON(err <= 0 || err >= 256);

	hdr = (struct sadb_msg *) skb_put(skb, sizeof(struct sadb_msg));
	pfkey_hdr_dup(hdr, orig);
	hdr->sadb_msg_errno = (uint8_t) err;
	hdr->sadb_msg_len = (sizeof(struct sadb_msg) /
			     sizeof(uint64_t));

	pfkey_broadcast(skb, GFP_KERNEL, BROADCAST_ONE, sk, sock_net(sk));

	return 0;
}