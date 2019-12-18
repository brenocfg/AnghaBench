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
struct mpic {int /*<<< orphan*/  gregs; int /*<<< orphan*/  reg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GREG_IPI_STRIDE ; 
 int /*<<< orphan*/  GREG_IPI_VECTOR_PRI_0 ; 
 unsigned int MPIC_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mpic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void _mpic_ipi_write(struct mpic *mpic, unsigned int ipi, u32 value)
{
	unsigned int offset = MPIC_INFO(GREG_IPI_VECTOR_PRI_0) +
			      (ipi * MPIC_INFO(GREG_IPI_STRIDE));

	_mpic_write(mpic->reg_type, &mpic->gregs, offset, value);
}