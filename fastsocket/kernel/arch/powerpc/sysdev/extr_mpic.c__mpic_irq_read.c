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
typedef  unsigned int u32 ;
struct mpic {unsigned int isu_shift; unsigned int isu_mask; unsigned int* isu_reg0_shadow; int /*<<< orphan*/ * isus; int /*<<< orphan*/  reg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_STRIDE ; 
 unsigned int MPIC_INFO (int /*<<< orphan*/ ) ; 
 unsigned int MPIC_VECPRI_ACTIVITY ; 
 unsigned int MPIC_VECPRI_MASK ; 
 unsigned int _mpic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline u32 _mpic_irq_read(struct mpic *mpic, unsigned int src_no, unsigned int reg)
{
	unsigned int	isu = src_no >> mpic->isu_shift;
	unsigned int	idx = src_no & mpic->isu_mask;
	unsigned int	val;

	val = _mpic_read(mpic->reg_type, &mpic->isus[isu],
			 reg + (idx * MPIC_INFO(IRQ_STRIDE)));
#ifdef CONFIG_MPIC_BROKEN_REGREAD
	if (reg == 0)
		val = (val & (MPIC_VECPRI_MASK | MPIC_VECPRI_ACTIVITY)) |
			mpic->isu_reg0_shadow[src_no];
#endif
	return val;
}