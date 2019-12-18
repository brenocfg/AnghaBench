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
struct sock {int sk_hash; } ;
struct hlist_head {int dummy; } ;
struct atm_vcc {int vci; } ;

/* Variables and functions */
 int VCC_HTABLE_SIZE ; 
 struct atm_vcc* atm_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,struct hlist_head*) ; 
 struct hlist_head* vcc_hash ; 

__attribute__((used)) static void __vcc_insert_socket(struct sock *sk)
{
	struct atm_vcc *vcc = atm_sk(sk);
	struct hlist_head *head = &vcc_hash[vcc->vci &
					(VCC_HTABLE_SIZE - 1)];
	sk->sk_hash = vcc->vci & (VCC_HTABLE_SIZE - 1);
	sk_add_node(sk, head);
}