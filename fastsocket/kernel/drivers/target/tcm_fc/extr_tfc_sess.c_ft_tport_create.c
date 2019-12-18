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
struct ft_tport {int /*<<< orphan*/ * hash; struct ft_tpg* tpg; struct fc_lport* lport; } ;
struct ft_tpg {struct ft_tport* tport; } ;
struct fc_lport {int /*<<< orphan*/ * prov; } ;

/* Variables and functions */
 size_t FC_TYPE_FCP ; 
 int FT_SESS_HASH_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ft_tpg* ft_lport_find_tpg (struct fc_lport*) ; 
 int /*<<< orphan*/  ft_lport_lock ; 
 struct ft_tport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct ft_tport*) ; 
 struct ft_tport* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ft_tport *ft_tport_create(struct fc_lport *lport)
{
	struct ft_tpg *tpg;
	struct ft_tport *tport;
	int i;

	tport = rcu_dereference_protected(lport->prov[FC_TYPE_FCP],
					  lockdep_is_held(&ft_lport_lock));
	if (tport && tport->tpg)
		return tport;

	tpg = ft_lport_find_tpg(lport);
	if (!tpg)
		return NULL;

	if (tport) {
		tport->tpg = tpg;
		return tport;
	}

	tport = kzalloc(sizeof(*tport), GFP_KERNEL);
	if (!tport)
		return NULL;

	tport->lport = lport;
	tport->tpg = tpg;
	tpg->tport = tport;
	for (i = 0; i < FT_SESS_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&tport->hash[i]);

	rcu_assign_pointer(lport->prov[FC_TYPE_FCP], tport);
	return tport;
}