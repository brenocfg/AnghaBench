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
struct t10_alua_tg_pt_gp_member {int tg_pt_gp_assoc; int /*<<< orphan*/  tg_pt_gp_mem_list; struct t10_alua_tg_pt_gp* tg_pt_gp; } ;
struct t10_alua_tg_pt_gp {int /*<<< orphan*/  tg_pt_gp_lock; int /*<<< orphan*/  tg_pt_gp_members; int /*<<< orphan*/  tg_pt_gp_mem_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __core_alua_attach_tg_pt_gp_mem(
	struct t10_alua_tg_pt_gp_member *tg_pt_gp_mem,
	struct t10_alua_tg_pt_gp *tg_pt_gp)
{
	spin_lock(&tg_pt_gp->tg_pt_gp_lock);
	tg_pt_gp_mem->tg_pt_gp = tg_pt_gp;
	tg_pt_gp_mem->tg_pt_gp_assoc = 1;
	list_add_tail(&tg_pt_gp_mem->tg_pt_gp_mem_list,
			&tg_pt_gp->tg_pt_gp_mem_list);
	tg_pt_gp->tg_pt_gp_members++;
	spin_unlock(&tg_pt_gp->tg_pt_gp_lock);
}