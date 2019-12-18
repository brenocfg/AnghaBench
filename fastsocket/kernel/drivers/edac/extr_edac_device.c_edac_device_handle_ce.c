#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ce_count; } ;
struct edac_device_instance {int nr_blocks; int /*<<< orphan*/  name; TYPE_2__ counters; struct edac_device_block* blocks; } ;
struct TYPE_6__ {int /*<<< orphan*/  ce_count; } ;
struct edac_device_ctl_info {int nr_instances; int /*<<< orphan*/  ctl_name; TYPE_3__ counters; struct edac_device_instance* instances; } ;
struct TYPE_4__ {int /*<<< orphan*/  ce_count; } ;
struct edac_device_block {char* name; TYPE_1__ counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ edac_device_get_log_ce (struct edac_device_ctl_info*) ; 
 int /*<<< orphan*/  edac_device_printk (struct edac_device_ctl_info*,int /*<<< orphan*/ ,char*,int,int,...) ; 

void edac_device_handle_ce(struct edac_device_ctl_info *edac_dev,
			int inst_nr, int block_nr, const char *msg)
{
	struct edac_device_instance *instance;
	struct edac_device_block *block = NULL;

	if ((inst_nr >= edac_dev->nr_instances) || (inst_nr < 0)) {
		edac_device_printk(edac_dev, KERN_ERR,
				"INTERNAL ERROR: 'instance' out of range "
				"(%d >= %d)\n", inst_nr,
				edac_dev->nr_instances);
		return;
	}

	instance = edac_dev->instances + inst_nr;

	if ((block_nr >= instance->nr_blocks) || (block_nr < 0)) {
		edac_device_printk(edac_dev, KERN_ERR,
				"INTERNAL ERROR: instance %d 'block' "
				"out of range (%d >= %d)\n",
				inst_nr, block_nr,
				instance->nr_blocks);
		return;
	}

	if (instance->nr_blocks > 0) {
		block = instance->blocks + block_nr;
		block->counters.ce_count++;
	}

	/* Propogate the count up the 'totals' tree */
	instance->counters.ce_count++;
	edac_dev->counters.ce_count++;

	if (edac_device_get_log_ce(edac_dev))
		edac_device_printk(edac_dev, KERN_WARNING,
				"CE: %s instance: %s block: %s '%s'\n",
				edac_dev->ctl_name, instance->name,
				block ? block->name : "N/A", msg);
}