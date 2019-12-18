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
struct sock_fprog {int len; int /*<<< orphan*/ * filter; } ;
struct sock_filter {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_filter; } ;
struct sk_filter {int len; int /*<<< orphan*/  insns; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct sk_filter*) ; 
 struct sk_filter* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int sk_chk_filter (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sk_filter_delayed_uncharge (struct sock*,struct sk_filter*) ; 
 int /*<<< orphan*/  sk_filter_uncharge (struct sock*,struct sk_filter*) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct sk_filter*,unsigned int) ; 
 struct sk_filter* sock_kmalloc (struct sock*,unsigned int,int /*<<< orphan*/ ) ; 

int sk_attach_filter(struct sock_fprog *fprog, struct sock *sk)
{
	struct sk_filter *fp, *old_fp;
	unsigned int fsize = sizeof(struct sock_filter) * fprog->len;
	int err;

	/* Make sure new filter is there and in the right amounts. */
	if (fprog->filter == NULL)
		return -EINVAL;

	fp = sock_kmalloc(sk, fsize+sizeof(*fp), GFP_KERNEL);
	if (!fp)
		return -ENOMEM;
	if (copy_from_user(fp->insns, fprog->filter, fsize)) {
		sock_kfree_s(sk, fp, fsize+sizeof(*fp));
		return -EFAULT;
	}

	atomic_set(&fp->refcnt, 1);
	fp->len = fprog->len;

	err = sk_chk_filter(fp->insns, fp->len);
	if (err) {
		sk_filter_uncharge(sk, fp);
		return err;
	}

	rcu_read_lock_bh();
	old_fp = rcu_dereference(sk->sk_filter);
	rcu_assign_pointer(sk->sk_filter, fp);
	rcu_read_unlock_bh();

	if (old_fp)
		sk_filter_delayed_uncharge(sk, old_fp);
	return 0;
}