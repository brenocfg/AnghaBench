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

/* Variables and functions */
 int /*<<< orphan*/  pfkey_table_grab () ; 
 int /*<<< orphan*/  pfkey_table_ungrab () ; 
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 

__attribute__((used)) static void pfkey_remove(struct sock *sk)
{
	pfkey_table_grab();
	sk_del_node_init(sk);
	pfkey_table_ungrab();
}