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
struct mpic {unsigned int isu_shift; unsigned int isu_mask; int* isu_reg0_shadow; int /*<<< orphan*/ * isus; int /*<<< orphan*/  reg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_STRIDE ; 
 unsigned int MPIC_INFO (int /*<<< orphan*/ ) ; 
 int MPIC_VECPRI_ACTIVITY ; 
 int MPIC_VECPRI_MASK ; 
 int /*<<< orphan*/  _mpic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static inline void _mpic_irq_write(struct mpic *mpic, unsigned int src_no,
				   unsigned int reg, u32 value)
{
	unsigned int	isu = src_no >> mpic->isu_shift;
	unsigned int	idx = src_no & mpic->isu_mask;

	_mpic_write(mpic->reg_type, &mpic->isus[isu],
		    reg + (idx * MPIC_INFO(IRQ_STRIDE)), value);

#ifdef CONFIG_MPIC_BROKEN_REGREAD
	if (reg == 0)
		mpic->isu_reg0_shadow[src_no] =
			value & ~(MPIC_VECPRI_MASK | MPIC_VECPRI_ACTIVITY);
#endif
}