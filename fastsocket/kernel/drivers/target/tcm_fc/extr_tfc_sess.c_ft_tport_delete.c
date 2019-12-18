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
struct ft_tport {struct ft_tpg* tpg; struct fc_lport* lport; } ;
struct ft_tpg {int /*<<< orphan*/ * tport; } ;
struct fc_lport {struct ft_tport** prov; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t FC_TYPE_FCP ; 
 int /*<<< orphan*/  ft_sess_delete_all (struct ft_tport*) ; 
 int /*<<< orphan*/  kfree_rcu (struct ft_tport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct ft_tport*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ft_tport_delete(struct ft_tport *tport)
{
	struct fc_lport *lport;
	struct ft_tpg *tpg;

	ft_sess_delete_all(tport);
	lport = tport->lport;
	BUG_ON(tport != lport->prov[FC_TYPE_FCP]);
	rcu_assign_pointer(lport->prov[FC_TYPE_FCP], NULL);

	tpg = tport->tpg;
	if (tpg) {
		tpg->tport = NULL;
		tport->tpg = NULL;
	}
	kfree_rcu(tport, rcu);
}