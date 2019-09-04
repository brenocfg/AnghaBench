#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; int tv_sec; } ;
typedef  int /*<<< orphan*/  stack ;
struct TYPE_7__ {void** msa_stack; void** msa_pstack; int msa_ptstamp; int msa_tstamp; scalar_t__ msa_depth; scalar_t__ msa_pdepth; int /*<<< orphan*/  msa_thread; int /*<<< orphan*/  msa_pthread; } ;
typedef  TYPE_1__ mcl_scratch_audit_t ;
struct TYPE_8__ {int /*<<< orphan*/ * mca_contents; } ;
typedef  TYPE_2__ mcache_audit_t ;
struct TYPE_9__ {int tv_usec; int tv_sec; } ;

/* Variables and functions */
 int MCACHE_STACK_DEPTH ; 
 TYPE_1__* MCA_SAVED_SCRATCH_PTR (TYPE_2__*) ; 
 scalar_t__ OSBacktrace (void**,int) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (void**,void**,int) ; 
 int /*<<< orphan*/  bzero (void**,int) ; 
 int /*<<< orphan*/  current_thread () ; 
 TYPE_4__ mb_start ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 

__attribute__((used)) static void
mcl_audit_scratch(mcache_audit_t *mca)
{
	void *stack[MCACHE_STACK_DEPTH + 1];
	mcl_scratch_audit_t *msa;
	struct timeval now;

	VERIFY(mca->mca_contents != NULL);
	msa = MCA_SAVED_SCRATCH_PTR(mca);

	msa->msa_pthread = msa->msa_thread;
	msa->msa_thread = current_thread();
	bcopy(msa->msa_stack, msa->msa_pstack, sizeof (msa->msa_pstack));
	msa->msa_pdepth = msa->msa_depth;
	bzero(stack, sizeof (stack));
	msa->msa_depth = OSBacktrace(stack, MCACHE_STACK_DEPTH + 1) - 1;
	bcopy(&stack[1], msa->msa_stack, sizeof (msa->msa_stack));

	msa->msa_ptstamp = msa->msa_tstamp;
	microuptime(&now);
	/* tstamp is in ms relative to base_ts */
	msa->msa_tstamp = ((now.tv_usec - mb_start.tv_usec) / 1000);
	if ((now.tv_sec - mb_start.tv_sec) > 0)
		msa->msa_tstamp += ((now.tv_sec - mb_start.tv_sec) * 1000);
}