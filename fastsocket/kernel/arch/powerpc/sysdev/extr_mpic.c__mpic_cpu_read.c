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
typedef  int /*<<< orphan*/  u32 ;
struct mpic {int flags; int /*<<< orphan*/ * cpuregs; int /*<<< orphan*/  reg_type; } ;

/* Variables and functions */
 int MPIC_PRIMARY ; 
 int /*<<< orphan*/  _mpic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int hard_smp_processor_id () ; 

__attribute__((used)) static inline u32 _mpic_cpu_read(struct mpic *mpic, unsigned int reg)
{
	unsigned int cpu = 0;

	if (mpic->flags & MPIC_PRIMARY)
		cpu = hard_smp_processor_id();
	return _mpic_read(mpic->reg_type, &mpic->cpuregs[cpu], reg);
}