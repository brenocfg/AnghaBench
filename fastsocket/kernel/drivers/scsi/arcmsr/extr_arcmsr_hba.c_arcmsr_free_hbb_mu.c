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
struct MessageUnit_B {int dummy; } ;
struct AdapterControlBlock {int adapter_type; int /*<<< orphan*/  dma_coherent_handle_hbb_mu; int /*<<< orphan*/  pmuB; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 130 
#define  ACB_ADAPTER_TYPE_B 129 
#define  ACB_ADAPTER_TYPE_C 128 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arcmsr_free_hbb_mu(struct AdapterControlBlock *acb)
{
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A:
	case ACB_ADAPTER_TYPE_C:
		break;
	case ACB_ADAPTER_TYPE_B:{
		dma_free_coherent(&acb->pdev->dev,
			sizeof(struct MessageUnit_B),
			acb->pmuB, acb->dma_coherent_handle_hbb_mu);
	}
	}
}