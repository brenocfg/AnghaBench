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
struct TYPE_4__ {scalar_t__ intr_type; } ;
struct vxgedev {int no_of_vpath; TYPE_3__* vpaths; int /*<<< orphan*/  napi; TYPE_1__ config; } ;
struct TYPE_5__ {int /*<<< orphan*/  napi; } ;
struct TYPE_6__ {TYPE_2__ ring; } ;

/* Variables and functions */
 scalar_t__ MSI_X ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vxge_napi_del_all(struct vxgedev *vdev)
{
	int i;
	if (vdev->config.intr_type != MSI_X)
		netif_napi_del(&vdev->napi);
	else {
		for (i = 0; i < vdev->no_of_vpath; i++)
			netif_napi_del(&vdev->vpaths[i].ring.napi);
	}
	return;
}