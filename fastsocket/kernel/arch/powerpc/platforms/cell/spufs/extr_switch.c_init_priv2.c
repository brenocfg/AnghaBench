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
struct TYPE_2__ {int mfc_control_RW; int /*<<< orphan*/  spu_lslr_RW; } ;
struct spu_state {TYPE_1__ priv2; } ;

/* Variables and functions */
 int /*<<< orphan*/  LS_ADDR_MASK ; 
 int MFC_CNTL_DMA_QUEUES_EMPTY_MASK ; 
 int MFC_CNTL_NORMAL_DMA_QUEUE_OPERATION ; 
 int MFC_CNTL_RESUME_DMA_QUEUE ; 

__attribute__((used)) static void init_priv2(struct spu_state *csa)
{
	csa->priv2.spu_lslr_RW = LS_ADDR_MASK;
	csa->priv2.mfc_control_RW = MFC_CNTL_RESUME_DMA_QUEUE |
	    MFC_CNTL_NORMAL_DMA_QUEUE_OPERATION |
	    MFC_CNTL_DMA_QUEUES_EMPTY_MASK;
}