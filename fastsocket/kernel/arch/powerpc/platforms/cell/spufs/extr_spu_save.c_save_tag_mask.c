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
struct TYPE_2__ {int /*<<< orphan*/ * slot; } ;

/* Variables and functions */
 unsigned int LSCSA_QW_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MFC_RdTagMask ; 
 TYPE_1__* regs_spill ; 
 int /*<<< orphan*/  spu_readch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tag_mask ; 

__attribute__((used)) static inline void save_tag_mask(void)
{
	unsigned int offset;

	/* Save, Step 3:
	 *    Read the SPU_RdTagMsk channel and save to the LSCSA.
	 */
	offset = LSCSA_QW_OFFSET(tag_mask);
	regs_spill[offset].slot[0] = spu_readch(MFC_RdTagMask);
}