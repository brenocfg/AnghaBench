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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_irq_composite_mask_config {int /*<<< orphan*/  ceDoneSel; int /*<<< orphan*/  viewIrqComMask; int /*<<< orphan*/  encIrqComMask; } ;
struct VFE_Irq_Composite_MaskType {int /*<<< orphan*/  ceDoneSelBits; int /*<<< orphan*/  viewIrqComMaskBits; int /*<<< orphan*/  encIrqComMaskBits; } ;
typedef  int /*<<< orphan*/  packedData ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct VFE_Irq_Composite_MaskType*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
vfe_irq_composite_pack(struct vfe_irq_composite_mask_config data)
{
	struct VFE_Irq_Composite_MaskType packedData;

	memset(&packedData, 0, sizeof(packedData));

	packedData.encIrqComMaskBits   = data.encIrqComMask;
	packedData.viewIrqComMaskBits  = data.viewIrqComMask;
	packedData.ceDoneSelBits       = data.ceDoneSel;

	return *((uint32_t *)&packedData);
}