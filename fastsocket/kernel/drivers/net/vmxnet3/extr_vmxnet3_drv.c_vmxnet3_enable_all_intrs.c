#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int num_intrs; } ;
struct vmxnet3_adapter {TYPE_4__* shared; TYPE_1__ intr; } ;
struct TYPE_6__ {int /*<<< orphan*/  intrCtrl; } ;
struct TYPE_7__ {TYPE_2__ intrConf; } ;
struct TYPE_8__ {TYPE_3__ devRead; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_IC_DISABLE_ALL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmxnet3_enable_intr (struct vmxnet3_adapter*,int) ; 

__attribute__((used)) static void
vmxnet3_enable_all_intrs(struct vmxnet3_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->intr.num_intrs; i++)
		vmxnet3_enable_intr(adapter, i);
	adapter->shared->devRead.intrConf.intrCtrl &=
					cpu_to_le32(~VMXNET3_IC_DISABLE_ALL);
}