#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct se_device {int dummy; } ;
struct pscsi_dev_virt {TYPE_2__* pdv_bd; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {TYPE_1__* bd_part; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_sects; } ;

/* Variables and functions */
 struct pscsi_dev_virt* PSCSI_DEV (struct se_device*) ; 
 int /*<<< orphan*/  dump_stack () ; 

__attribute__((used)) static sector_t pscsi_get_blocks(struct se_device *dev)
{
	struct pscsi_dev_virt *pdv = PSCSI_DEV(dev);

	if (pdv->pdv_bd && pdv->pdv_bd->bd_part)
		return pdv->pdv_bd->bd_part->nr_sects;

	dump_stack();
	return 0;
}