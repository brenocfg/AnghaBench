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
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int pci_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_INFORMANT ; 
 int QLCRDX (TYPE_1__*,int /*<<< orphan*/ ) ; 

void qlcnic_83xx_get_func_no(struct qlcnic_adapter *adapter)
{
	u32 val = QLCRDX(adapter->ahw, QLCNIC_INFORMANT);
	adapter->ahw->pci_func = (val >> 24) & 0xff;
}