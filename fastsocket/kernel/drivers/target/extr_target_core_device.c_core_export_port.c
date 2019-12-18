#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct t10_alua_tg_pt_gp_member {int /*<<< orphan*/  tg_pt_gp_mem_lock; } ;
struct se_portal_group {TYPE_4__* se_tpg_tfo; } ;
struct se_port {int /*<<< orphan*/  sep_rtpi; int /*<<< orphan*/  sep_index; int /*<<< orphan*/  sep_list; struct se_lun* sep_lun; struct se_portal_group* sep_tpg; } ;
struct se_lun {int /*<<< orphan*/  lun_sep_lock; struct se_port* lun_sep; } ;
struct TYPE_6__ {int /*<<< orphan*/  default_tg_pt_gp; } ;
struct se_device {int /*<<< orphan*/  dev_port_count; TYPE_3__* transport; TYPE_2__ t10_alua; TYPE_1__* se_hba; int /*<<< orphan*/  se_port_lock; int /*<<< orphan*/  dev_sep_list; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* get_fabric_name ) () ;} ;
struct TYPE_7__ {scalar_t__ transport_type; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int hba_flags; } ;

/* Variables and functions */
 int HBA_FLAGS_INTERNAL_USE ; 
 scalar_t__ IS_ERR (struct t10_alua_tg_pt_gp_member*) ; 
 scalar_t__ TRANSPORT_PLUGIN_PHBA_PDEV ; 
 int /*<<< orphan*/  __core_alua_attach_tg_pt_gp_mem (struct t10_alua_tg_pt_gp_member*,int /*<<< orphan*/ ) ; 
 struct t10_alua_tg_pt_gp_member* core_alua_allocate_tg_pt_gp_mem (struct se_port*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void core_export_port(
	struct se_device *dev,
	struct se_portal_group *tpg,
	struct se_port *port,
	struct se_lun *lun)
{
	struct t10_alua_tg_pt_gp_member *tg_pt_gp_mem = NULL;

	spin_lock(&dev->se_port_lock);
	spin_lock(&lun->lun_sep_lock);
	port->sep_tpg = tpg;
	port->sep_lun = lun;
	lun->lun_sep = port;
	spin_unlock(&lun->lun_sep_lock);

	list_add_tail(&port->sep_list, &dev->dev_sep_list);
	spin_unlock(&dev->se_port_lock);

	if (dev->transport->transport_type != TRANSPORT_PLUGIN_PHBA_PDEV &&
	    !(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE)) {
		tg_pt_gp_mem = core_alua_allocate_tg_pt_gp_mem(port);
		if (IS_ERR(tg_pt_gp_mem) || !tg_pt_gp_mem) {
			pr_err("Unable to allocate t10_alua_tg_pt"
					"_gp_member_t\n");
			return;
		}
		spin_lock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
		__core_alua_attach_tg_pt_gp_mem(tg_pt_gp_mem,
			dev->t10_alua.default_tg_pt_gp);
		spin_unlock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
		pr_debug("%s/%s: Adding to default ALUA Target Port"
			" Group: alua/default_tg_pt_gp\n",
			dev->transport->name, tpg->se_tpg_tfo->get_fabric_name());
	}

	dev->dev_port_count++;
	port->sep_index = port->sep_rtpi; /* RELATIVE TARGET PORT IDENTIFIER */
}