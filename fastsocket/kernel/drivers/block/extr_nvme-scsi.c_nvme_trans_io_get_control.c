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
typedef  int /*<<< orphan*/  u16 ;
struct nvme_trans_io_cdb {scalar_t__ fua; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_RW_FUA ; 

__attribute__((used)) static u16 nvme_trans_io_get_control(struct nvme_ns *ns,
					struct nvme_trans_io_cdb *cdb_info)
{
	u16 control = 0;

	/* When Protection information support is added, implement here */

	if (cdb_info->fua > 0)
		control |= NVME_RW_FUA;

	return control;
}