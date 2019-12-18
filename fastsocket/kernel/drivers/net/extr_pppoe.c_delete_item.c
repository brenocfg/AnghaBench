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
struct pppox_sock {int dummy; } ;
struct pppoe_net {int /*<<< orphan*/  hash_lock; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct pppox_sock* __delete_item (struct pppoe_net*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct pppox_sock *delete_item(struct pppoe_net *pn, __be16 sid,
					char *addr, int ifindex)
{
	struct pppox_sock *ret;

	write_lock_bh(&pn->hash_lock);
	ret = __delete_item(pn, sid, addr, ifindex);
	write_unlock_bh(&pn->hash_lock);

	return ret;
}