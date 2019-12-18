#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int vdev_ashift; struct TYPE_4__* vdev_top; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_label_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uberblock_t ;

/* Variables and functions */
 int VDEV_UBERBLOCK_COUNT (TYPE_1__*) ; 
 int VDEV_UBERBLOCK_OFFSET (TYPE_1__*,int) ; 
 int ZDB_MAX_UB_HEADER_SIZE ; 
 int /*<<< orphan*/  dump_uberblock (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ uberblock_verify (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_label_uberblocks(vdev_label_t *lbl, uint64_t ashift)
{
	vdev_t vd;
	vdev_t *vdp = &vd;
	char header[ZDB_MAX_UB_HEADER_SIZE];

	vd.vdev_ashift = ashift;
	vdp->vdev_top = vdp;

	for (int i = 0; i < VDEV_UBERBLOCK_COUNT(vdp); i++) {
		uint64_t uoff = VDEV_UBERBLOCK_OFFSET(vdp, i);
		uberblock_t *ub = (void *)((char *)lbl + uoff);

		if (uberblock_verify(ub))
			continue;
		(void) snprintf(header, ZDB_MAX_UB_HEADER_SIZE,
		    "Uberblock[%d]\n", i);
		dump_uberblock(ub, header, "");
	}
}