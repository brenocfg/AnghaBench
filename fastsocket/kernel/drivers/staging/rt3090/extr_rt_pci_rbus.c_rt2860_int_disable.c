#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {unsigned int int_disable_mask; int int_enable_reg; } ;
typedef  TYPE_1__* PRTMP_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK_CSR ; 
 int /*<<< orphan*/  RTMP_CLEAR_FLAG (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTMP_IO_WRITE32 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_INTERRUPT_ACTIVE ; 

__attribute__((used)) static inline void rt2860_int_disable(PRTMP_ADAPTER pAd, unsigned int mode)
{
	u32 regValue;

	pAd->int_disable_mask |= mode;
	regValue =	pAd->int_enable_reg & ~(pAd->int_disable_mask);
	RTMP_IO_WRITE32(pAd, INT_MASK_CSR, regValue);     // 0: disable

	if (regValue == 0)
	{
		RTMP_CLEAR_FLAG(pAd, fRTMP_ADAPTER_INTERRUPT_ACTIVE);
	}
}