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
struct qib_ibport {int dummy; } ;
struct qib_devdata {unsigned int num_pports; TYPE_1__* pport; } ;
struct ib_device_modify {int /*<<< orphan*/  sys_image_guid; int /*<<< orphan*/  node_desc; } ;
struct ib_device {int /*<<< orphan*/  node_desc; } ;
struct TYPE_2__ {struct qib_ibport ibport_data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IB_DEVICE_MODIFY_NODE_DESC ; 
 int IB_DEVICE_MODIFY_SYS_IMAGE_GUID ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct qib_devdata* dd_from_ibdev (struct ib_device*) ; 
 int /*<<< orphan*/  ib_qib_sys_image_guid ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qib_node_desc_chg (struct qib_ibport*) ; 
 int /*<<< orphan*/  qib_sys_guid_chg (struct qib_ibport*) ; 

__attribute__((used)) static int qib_modify_device(struct ib_device *device,
			     int device_modify_mask,
			     struct ib_device_modify *device_modify)
{
	struct qib_devdata *dd = dd_from_ibdev(device);
	unsigned i;
	int ret;

	if (device_modify_mask & ~(IB_DEVICE_MODIFY_SYS_IMAGE_GUID |
				   IB_DEVICE_MODIFY_NODE_DESC)) {
		ret = -EOPNOTSUPP;
		goto bail;
	}

	if (device_modify_mask & IB_DEVICE_MODIFY_NODE_DESC) {
		memcpy(device->node_desc, device_modify->node_desc, 64);
		for (i = 0; i < dd->num_pports; i++) {
			struct qib_ibport *ibp = &dd->pport[i].ibport_data;

			qib_node_desc_chg(ibp);
		}
	}

	if (device_modify_mask & IB_DEVICE_MODIFY_SYS_IMAGE_GUID) {
		ib_qib_sys_image_guid =
			cpu_to_be64(device_modify->sys_image_guid);
		for (i = 0; i < dd->num_pports; i++) {
			struct qib_ibport *ibp = &dd->pport[i].ibport_data;

			qib_sys_guid_chg(ibp);
		}
	}

	ret = 0;

bail:
	return ret;
}