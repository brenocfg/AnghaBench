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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {unsigned short device; } ;

/* Variables and functions */
 unsigned short PCI_DEVICE_ID_QLOGIC_QLE834X ; 
 unsigned short PCI_DEVICE_ID_QLOGIC_VF_QLE834X ; 

__attribute__((used)) static inline u32 qlcnic_get_ref_handle(struct qlcnic_adapter *adapter,
					u16 handle, u8 ring_id)
{
	unsigned short device = adapter->pdev->device;

	if ((device == PCI_DEVICE_ID_QLOGIC_QLE834X) ||
	    (device == PCI_DEVICE_ID_QLOGIC_VF_QLE834X))
		return handle | (ring_id << 15);
	else
		return handle;
}