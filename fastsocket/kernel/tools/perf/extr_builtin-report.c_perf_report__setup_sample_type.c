#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct perf_session {int /*<<< orphan*/  fd_pipe; int /*<<< orphan*/  evlist; } ;
struct perf_report {int /*<<< orphan*/  dont_use_callchains; struct perf_session* session; } ;
struct TYPE_5__ {scalar_t__ mode; } ;
struct TYPE_4__ {int use_callchain; } ;

/* Variables and functions */
 scalar_t__ CHAIN_NONE ; 
 int EINVAL ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_CALLCHAIN ; 
 TYPE_2__ callchain_param ; 
 scalar_t__ callchain_register_param (TYPE_2__*) ; 
 int perf_evlist__sample_type (int /*<<< orphan*/ ) ; 
 int sort__branch_mode ; 
 scalar_t__ sort__has_parent ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  ui__error (char*) ; 

__attribute__((used)) static int perf_report__setup_sample_type(struct perf_report *rep)
{
	struct perf_session *self = rep->session;
	u64 sample_type = perf_evlist__sample_type(self->evlist);

	if (!self->fd_pipe && !(sample_type & PERF_SAMPLE_CALLCHAIN)) {
		if (sort__has_parent) {
			ui__error("Selected --sort parent, but no "
				    "callchain data. Did you call "
				    "'perf record' without -g?\n");
			return -EINVAL;
		}
		if (symbol_conf.use_callchain) {
			ui__error("Selected -g but no callchain data. Did "
				    "you call 'perf record' without -g?\n");
			return -1;
		}
	} else if (!rep->dont_use_callchains &&
		   callchain_param.mode != CHAIN_NONE &&
		   !symbol_conf.use_callchain) {
			symbol_conf.use_callchain = true;
			if (callchain_register_param(&callchain_param) < 0) {
				ui__error("Can't register callchain params.\n");
				return -EINVAL;
			}
	}

	if (sort__branch_mode == 1) {
		if (!self->fd_pipe &&
		    !(sample_type & PERF_SAMPLE_BRANCH_STACK)) {
			ui__error("Selected -b but no branch data. "
				  "Did you call perf record without -b?\n");
			return -1;
		}
	}

	return 0;
}