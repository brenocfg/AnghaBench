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

/* Variables and functions */
 int BCOM_DRD_INITIATOR_SHIFT ; 

__attribute__((used)) static inline void
bcom_set_desc_initiator(u32 *desc, int initiator)
{
	*desc = (*desc & ~(0x1f << BCOM_DRD_INITIATOR_SHIFT)) |
			((initiator & 0x1f) << BCOM_DRD_INITIATOR_SHIFT);
}