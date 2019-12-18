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
typedef  int uint32_t ;
struct TYPE_6__ {TYPE_2__* pTail; } ;
struct TYPE_4__ {int lo; } ;
struct TYPE_5__ {TYPE_1__ ctl; } ;

/* Variables and functions */
 TYPE_3__* dmacHw_GET_DESC_RING (void*) ; 
 int dmacHw_REG_CTL_TTFC_MASK ; 
#define  dmacHw_REG_CTL_TTFC_MM_DMAC 131 
#define  dmacHw_REG_CTL_TTFC_MP_DMAC 130 
#define  dmacHw_REG_CTL_TTFC_PM_DMAC 129 
#define  dmacHw_REG_CTL_TTFC_PP_DMAC 128 

__attribute__((used)) static inline int DmaIsFlowController(void *pDescriptor	/*   [ IN ] Descriptor buffer */
    ) {
	uint32_t ttfc =
	    (dmacHw_GET_DESC_RING(pDescriptor))->pTail->ctl.
	    lo & dmacHw_REG_CTL_TTFC_MASK;

	switch (ttfc) {
	case dmacHw_REG_CTL_TTFC_MM_DMAC:
	case dmacHw_REG_CTL_TTFC_MP_DMAC:
	case dmacHw_REG_CTL_TTFC_PM_DMAC:
	case dmacHw_REG_CTL_TTFC_PP_DMAC:
		return 1;
	}

	return 0;
}