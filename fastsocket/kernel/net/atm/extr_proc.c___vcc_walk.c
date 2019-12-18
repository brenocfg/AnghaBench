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
struct sock {int dummy; } ;
struct hlist_head {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct sock* SEQ_START_TOKEN ; 
 int VCC_HTABLE_SIZE ; 
 struct sock* __sk_head (struct hlist_head*) ; 
 scalar_t__ compare_family (struct sock*,int) ; 
 scalar_t__ hlist_empty (struct hlist_head*) ; 
 struct sock* sk_head (struct hlist_head*) ; 
 struct sock* sk_next (struct sock*) ; 
 struct hlist_head* vcc_hash ; 

__attribute__((used)) static int __vcc_walk(struct sock **sock, int family, int *bucket, loff_t l)
{
	struct sock *sk = *sock;

	if (sk == SEQ_START_TOKEN) {
		for (*bucket = 0; *bucket < VCC_HTABLE_SIZE; ++*bucket) {
			struct hlist_head *head = &vcc_hash[*bucket];

			sk = hlist_empty(head) ? NULL : __sk_head(head);
			if (sk)
				break;
		}
		l--;
	}
try_again:
	for (; sk; sk = sk_next(sk)) {
		l -= compare_family(sk, family);
		if (l < 0)
			goto out;
	}
	if (!sk && ++*bucket < VCC_HTABLE_SIZE) {
		sk = sk_head(&vcc_hash[*bucket]);
		goto try_again;
	}
	sk = SEQ_START_TOKEN;
out:
	*sock = sk;
	return (l < 0);
}