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
struct spu_state {int /*<<< orphan*/  lscsa; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spu_invalidate_slbs (struct spu*) ; 
 int /*<<< orphan*/  spu_setup_kernel_slbs (struct spu*,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static inline void setup_mfc_slbs(struct spu_state *csa, struct spu *spu,
		unsigned int *code, int code_size)
{
	/* Save, Step 47:
	 * Restore, Step 30.
	 *     If MFC_SR1[R]=1, write 0 to SLB_Invalidate_All
	 *     register, then initialize SLB_VSID and SLB_ESID
	 *     to provide access to SPU context save code and
	 *     LSCSA.
	 *
	 *     This implementation places both the context
	 *     switch code and LSCSA in kernel address space.
	 *
	 *     Further this implementation assumes that the
	 *     MFC_SR1[R]=1 (in other words, assume that
	 *     translation is desired by OS environment).
	 */
	spu_invalidate_slbs(spu);
	spu_setup_kernel_slbs(spu, csa->lscsa, code, code_size);
}