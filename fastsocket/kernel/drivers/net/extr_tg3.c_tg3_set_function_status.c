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
struct tg3 {int pci_fn; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5717 ; 
 scalar_t__ ASIC_REV_5719 ; 
 int /*<<< orphan*/  TG3_APE_GPIO_MSG ; 
 int TG3_APE_GPIO_MSG_SHIFT ; 
 int /*<<< orphan*/  TG3_CPMU_DRV_STATUS ; 
 int TG3_GPIO_MSG_MASK ; 
 int tg3_ape_read32 (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_ape_write32 (struct tg3*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 tg3_set_function_status(struct tg3 *tp, u32 newstat)
{
	u32 status, shift;

	if (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719)
		status = tg3_ape_read32(tp, TG3_APE_GPIO_MSG);
	else
		status = tr32(TG3_CPMU_DRV_STATUS);

	shift = TG3_APE_GPIO_MSG_SHIFT + 4 * tp->pci_fn;
	status &= ~(TG3_GPIO_MSG_MASK << shift);
	status |= (newstat << shift);

	if (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719)
		tg3_ape_write32(tp, TG3_APE_GPIO_MSG, status);
	else
		tw32(TG3_CPMU_DRV_STATUS, status);

	return status >> TG3_APE_GPIO_MSG_SHIFT;
}