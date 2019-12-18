#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct seq_file {TYPE_5__* private; } ;
struct TYPE_8__ {TYPE_2__** crypt; } ;
struct TYPE_10__ {int fw_tx_rate_control; int beacon_int; int dtim_period; int wds_max_connections; int dev_enabled; int sw_tick_stuck; int pri_only; int sram_type; int no_pri; TYPE_4__* func; TYPE_3__ crypt_info; int /*<<< orphan*/ * intransmitfid; int /*<<< orphan*/ * txfid; int /*<<< orphan*/  next_alloc; int /*<<< orphan*/  next_txfid; } ;
typedef  TYPE_5__ local_info_t ;
struct TYPE_9__ {scalar_t__ hw_type; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ HOSTAP_HW_PCI ; 
 int PRISM2_TXFID_COUNT ; 
 int WEP_KEYS ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 

__attribute__((used)) static int prism2_debug_proc_show(struct seq_file *m, void *v)
{
	local_info_t *local = m->private;
	int i;

	seq_printf(m, "next_txfid=%d next_alloc=%d\n",
		   local->next_txfid, local->next_alloc);
	for (i = 0; i < PRISM2_TXFID_COUNT; i++)
		seq_printf(m, "FID: tx=%04X intransmit=%04X\n",
			   local->txfid[i], local->intransmitfid[i]);
	seq_printf(m, "FW TX rate control: %d\n", local->fw_tx_rate_control);
	seq_printf(m, "beacon_int=%d\n", local->beacon_int);
	seq_printf(m, "dtim_period=%d\n", local->dtim_period);
	seq_printf(m, "wds_max_connections=%d\n", local->wds_max_connections);
	seq_printf(m, "dev_enabled=%d\n", local->dev_enabled);
	seq_printf(m, "sw_tick_stuck=%d\n", local->sw_tick_stuck);
	for (i = 0; i < WEP_KEYS; i++) {
		if (local->crypt_info.crypt[i] &&
		    local->crypt_info.crypt[i]->ops) {
			seq_printf(m, "crypt[%d]=%s\n", i,
				   local->crypt_info.crypt[i]->ops->name);
		}
	}
	seq_printf(m, "pri_only=%d\n", local->pri_only);
	seq_printf(m, "pci=%d\n", local->func->hw_type == HOSTAP_HW_PCI);
	seq_printf(m, "sram_type=%d\n", local->sram_type);
	seq_printf(m, "no_pri=%d\n", local->no_pri);

	return 0;
}