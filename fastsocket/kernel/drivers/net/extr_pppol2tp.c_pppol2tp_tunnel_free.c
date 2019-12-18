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
struct pppol2tp_tunnel {int /*<<< orphan*/  list; int /*<<< orphan*/  pppol2tp_net; } ;
struct pppol2tp_net {int /*<<< orphan*/  pppol2tp_tunnel_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pppol2tp_tunnel*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct pppol2tp_net* pppol2tp_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pppol2tp_tunnel_count ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pppol2tp_tunnel_free(struct pppol2tp_tunnel *tunnel)
{
	struct pppol2tp_net *pn = pppol2tp_pernet(tunnel->pppol2tp_net);

	/* Remove from socket list */
	write_lock_bh(&pn->pppol2tp_tunnel_list_lock);
	list_del_init(&tunnel->list);
	write_unlock_bh(&pn->pppol2tp_tunnel_list_lock);

	atomic_dec(&pppol2tp_tunnel_count);
	kfree(tunnel);
}