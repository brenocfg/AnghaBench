#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kperf_sample {int dummy; } ;
struct kperf_context {int cur_pid; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_2__ {int pid_filter; unsigned int sample; int /*<<< orphan*/  ucallstack_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAMPLE_CONTINUE ; 
 int /*<<< orphan*/  SAMPLE_SHUTDOWN ; 
 unsigned int actionc ; 
 TYPE_1__* actionv ; 
 int /*<<< orphan*/  kperf_sample_internal (struct kperf_sample*,struct kperf_context*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

kern_return_t
kperf_sample(struct kperf_sample *sbuf,
             struct kperf_context *context,
             unsigned actionid, unsigned sample_flags)
{
	/* work out what to sample, if anything */
	if ((actionid > actionc) || (actionid == 0)) {
		return SAMPLE_SHUTDOWN;
	}

	/* check the pid filter against the context's current pid.
	 * filter pid == -1 means any pid
	 */
	int pid_filter = actionv[actionid - 1].pid_filter;
	if ((pid_filter != -1) && (pid_filter != context->cur_pid)) {
		return SAMPLE_CONTINUE;
	}

	/* the samplers to run */
	unsigned int sample_what = actionv[actionid - 1].sample;

	/* do the actual sample operation */
	return kperf_sample_internal(sbuf, context, sample_what,
	                             sample_flags, actionid,
	                             actionv[actionid - 1].ucallstack_depth);
}