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
struct ipx_interface {int /*<<< orphan*/  if_sklist_lock; int /*<<< orphan*/  if_sklist; } ;
struct TYPE_2__ {struct ipx_interface* intrfc; } ;

/* Variables and functions */
 TYPE_1__* ipx_sk (struct sock*) ; 
 int /*<<< orphan*/  ipxitf_hold (struct ipx_interface*) ; 
 int /*<<< orphan*/  ipxitf_put (struct ipx_interface*) ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipxitf_insert_socket(struct ipx_interface *intrfc, struct sock *sk)
{
	ipxitf_hold(intrfc);
	spin_lock_bh(&intrfc->if_sklist_lock);
	ipx_sk(sk)->intrfc = intrfc;
	sk_add_node(sk, &intrfc->if_sklist);
	spin_unlock_bh(&intrfc->if_sklist_lock);
	ipxitf_put(intrfc);
}