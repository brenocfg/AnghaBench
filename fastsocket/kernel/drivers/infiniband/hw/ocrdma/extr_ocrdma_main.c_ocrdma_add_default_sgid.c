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
struct TYPE_2__ {int /*<<< orphan*/  subnet_prefix; } ;
union ib_gid {int /*<<< orphan*/ * raw; TYPE_1__ global; } ;
struct ocrdma_dev {union ib_gid* sgid_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  ocrdma_get_guid (struct ocrdma_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocrdma_add_default_sgid(struct ocrdma_dev *dev)
{
	/* GID Index 0 - Invariant manufacturer-assigned EUI-64 */
	union ib_gid *sgid = &dev->sgid_tbl[0];

	sgid->global.subnet_prefix = cpu_to_be64(0xfe80000000000000LL);
	ocrdma_get_guid(dev, &sgid->raw[8]);
}