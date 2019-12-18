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
struct spu_state {int dummy; } ;
struct spu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void enable_user_access(struct spu_state *csa, struct spu *spu)
{
	/* Restore, Step 73:
	 *     Enable user-space access (if provided) to this
	 *     SPU by mapping the virtual pages assigned to
	 *     the SPU memory-mapped I/O (MMIO) for problem
	 *     state. TBD.
	 */
}