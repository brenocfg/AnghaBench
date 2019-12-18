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
struct xt_tgdtor_param {TYPE_1__* target; struct ipt_clusterip_tgt_info* targinfo; } ;
struct ipt_clusterip_tgt_info {int /*<<< orphan*/  config; } ;
struct TYPE_2__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  clusterip_config_entry_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterip_config_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_l3proto_module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clusterip_tg_destroy(const struct xt_tgdtor_param *par)
{
	const struct ipt_clusterip_tgt_info *cipinfo = par->targinfo;

	/* if no more entries are referencing the config, remove it
	 * from the list and destroy the proc entry */
	clusterip_config_entry_put(cipinfo->config);

	clusterip_config_put(cipinfo->config);

	nf_ct_l3proto_module_put(par->target->family);
}