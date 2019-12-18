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
 int check_restore_status (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_csa (struct spu_state*,struct spu*) ; 
 int /*<<< orphan*/  restore_lscsa (struct spu_state*,struct spu*) ; 

__attribute__((used)) static int __do_spu_restore(struct spu_state *next, struct spu *spu)
{
	int rc;

	/*
	 * SPU context restore can be broken into three phases:
	 *
	 *    (a) harvest (or reset) SPU [steps 2-24].
	 *    (b) restore LSCSA [steps 25-40], mostly performed by SPU.
	 *    (c) restore CSA [steps 41-76], performed by PPE.
	 *
	 * The 'harvest' step is not performed here, but rather
	 * as needed below.
	 */

	restore_lscsa(next, spu);	        /* Steps 24-39. */
	rc = check_restore_status(next, spu);	/* Step 40.     */
	switch (rc) {
	default:
		/* Failed. Return now. */
		return rc;
		break;
	case 0:
		/* Fall through to next step. */
		break;
	}
	restore_csa(next, spu);

	return 0;
}