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
struct TYPE_2__ {unsigned int* slot; } ;

/* Variables and functions */
 unsigned int LSCSA_QW_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  MFC_WrTagMask ; 
 TYPE_1__* regs_spill ; 
 int /*<<< orphan*/  spu_writech (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void restore_tag_mask(void)
{
	unsigned int offset;
	unsigned int tag_mask;

	/* Restore, Step 16:
	 *    Restore the SPU_RdTagMsk data from the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(tag_mask);
	tag_mask = regs_spill[offset].slot[0];
	spu_writech(MFC_WrTagMask, tag_mask);
}