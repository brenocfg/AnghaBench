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
struct t10_alua_tg_pt_gp_member {int /*<<< orphan*/  tg_pt_gp_mem_lock; struct t10_alua_tg_pt_gp* tg_pt_gp; scalar_t__ tg_pt_gp_assoc; int /*<<< orphan*/  tg_pt_gp_mem_list; int /*<<< orphan*/  tg_pt_gp_mem_ref_cnt; } ;
struct t10_alua_tg_pt_gp {int /*<<< orphan*/  tg_pt_gp_lock; int /*<<< orphan*/  tg_pt_gp_members; } ;
struct se_port {struct t10_alua_tg_pt_gp_member* sep_alua_tg_pt_gp_mem; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct t10_alua_tg_pt_gp_member*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t10_alua_tg_pt_gp_mem_cache ; 

void core_alua_free_tg_pt_gp_mem(struct se_port *port)
{
	struct t10_alua_tg_pt_gp *tg_pt_gp;
	struct t10_alua_tg_pt_gp_member *tg_pt_gp_mem;

	tg_pt_gp_mem = port->sep_alua_tg_pt_gp_mem;
	if (!tg_pt_gp_mem)
		return;

	while (atomic_read(&tg_pt_gp_mem->tg_pt_gp_mem_ref_cnt))
		cpu_relax();

	spin_lock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
	tg_pt_gp = tg_pt_gp_mem->tg_pt_gp;
	if (tg_pt_gp) {
		spin_lock(&tg_pt_gp->tg_pt_gp_lock);
		if (tg_pt_gp_mem->tg_pt_gp_assoc) {
			list_del(&tg_pt_gp_mem->tg_pt_gp_mem_list);
			tg_pt_gp->tg_pt_gp_members--;
			tg_pt_gp_mem->tg_pt_gp_assoc = 0;
		}
		spin_unlock(&tg_pt_gp->tg_pt_gp_lock);
		tg_pt_gp_mem->tg_pt_gp = NULL;
	}
	spin_unlock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);

	kmem_cache_free(t10_alua_tg_pt_gp_mem_cache, tg_pt_gp_mem);
}