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
struct sock {int dummy; } ;
struct ipx_interface {int /*<<< orphan*/  if_sklist_lock; } ;
struct TYPE_2__ {struct ipx_interface* intrfc; } ;

/* Variables and functions */
 TYPE_1__* ipx_sk (struct sock*) ; 
 int /*<<< orphan*/  ipxitf_hold (struct ipx_interface*) ; 
 int /*<<< orphan*/  ipxitf_put (struct ipx_interface*) ; 
 int /*<<< orphan*/  sk_del_node_init (struct sock*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipx_remove_socket(struct sock *sk)
{
	/* Determine interface with which socket is associated */
	struct ipx_interface *intrfc = ipx_sk(sk)->intrfc;

	if (!intrfc)
		goto out;

	ipxitf_hold(intrfc);
	spin_lock_bh(&intrfc->if_sklist_lock);
	sk_del_node_init(sk);
	spin_unlock_bh(&intrfc->if_sklist_lock);
	ipxitf_put(intrfc);
out:
	return;
}