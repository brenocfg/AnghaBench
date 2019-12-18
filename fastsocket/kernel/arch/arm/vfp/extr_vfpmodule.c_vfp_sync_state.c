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
struct thread_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPEXC ; 
 int FPEXC_EN ; 
 int fmrx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmxr (int /*<<< orphan*/ ,int) ; 
 unsigned int get_cpu () ; 
 int /*<<< orphan*/ ** last_VFP_context ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  vfp_save_state (int /*<<< orphan*/ *,int) ; 

void vfp_sync_state(struct thread_info *thread)
{
	unsigned int cpu = get_cpu();
	u32 fpexc = fmrx(FPEXC);

	/*
	 * If VFP is enabled, the previous state was already saved and
	 * last_VFP_context updated.
	 */
	if (fpexc & FPEXC_EN)
		goto out;

	if (!last_VFP_context[cpu])
		goto out;

	/*
	 * Save the last VFP state on this CPU.
	 */
	fmxr(FPEXC, fpexc | FPEXC_EN);
	vfp_save_state(last_VFP_context[cpu], fpexc);
	fmxr(FPEXC, fpexc);

	/*
	 * Set the context to NULL to force a reload the next time the thread
	 * uses the VFP.
	 */
	last_VFP_context[cpu] = NULL;

out:
	put_cpu();
}