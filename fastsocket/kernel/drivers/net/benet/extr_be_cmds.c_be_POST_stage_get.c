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
typedef  int u32 ;
typedef  int u16 ;
struct be_adapter {int /*<<< orphan*/  pdev; scalar_t__ csr; } ;

/* Variables and functions */
 scalar_t__ BEx_chip (struct be_adapter*) ; 
 int POST_STAGE_MASK ; 
 scalar_t__ SLIPORT_SEMAPHORE_OFFSET_BEx ; 
 int /*<<< orphan*/  SLIPORT_SEMAPHORE_OFFSET_SH ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u16 be_POST_stage_get(struct be_adapter *adapter)
{
	u32 sem;

	if (BEx_chip(adapter))
		sem  = ioread32(adapter->csr + SLIPORT_SEMAPHORE_OFFSET_BEx);
	else
		pci_read_config_dword(adapter->pdev,
				      SLIPORT_SEMAPHORE_OFFSET_SH, &sem);

	return sem & POST_STAGE_MASK;
}