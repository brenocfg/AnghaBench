#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* run_queue_t ;
typedef  scalar_t__ processor_t ;
typedef  int ast_t ;
struct TYPE_3__ {int count; int urgency; } ;

/* Variables and functions */
 int AST_NONE ; 
 int AST_PREEMPT ; 
 int AST_URGENT ; 
 TYPE_1__* global_runq ; 
 scalar_t__ proto_processor ; 

__attribute__((used)) static ast_t
sched_proto_processor_csw_check(processor_t processor)
{
	run_queue_t		runq;
	int				count, urgency;
	
	runq = global_runq;
	count = runq->count;
	urgency = runq->urgency;
	
	if (count > 0) {
		if (urgency > 0)
			return (AST_PREEMPT | AST_URGENT);
		
		return AST_PREEMPT;
	}

	if (proto_processor != processor)
		return AST_PREEMPT;

	return AST_NONE;
}