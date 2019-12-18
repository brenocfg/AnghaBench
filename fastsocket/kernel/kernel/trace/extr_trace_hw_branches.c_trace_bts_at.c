#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bts_trace {int (* read ) (int /*<<< orphan*/ ,void*,struct bts_struct*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;
struct TYPE_3__ {TYPE_2__ lbr; } ;
struct bts_struct {int qualifier; TYPE_1__ variant; } ;

/* Variables and functions */
#define  BTS_BRANCH 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int stub1 (int /*<<< orphan*/ ,void*,struct bts_struct*) ; 
 int /*<<< orphan*/  this_tracer ; 
 int /*<<< orphan*/  trace_hw_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trace_bts_at(const struct bts_trace *trace, void *at)
{
	struct bts_struct bts;
	int err = 0;

	WARN_ON_ONCE(!trace->read);
	if (!trace->read)
		return;

	err = trace->read(this_tracer, at, &bts);
	if (err < 0)
		return;

	switch (bts.qualifier) {
	case BTS_BRANCH:
		trace_hw_branch(bts.variant.lbr.from, bts.variant.lbr.to);
		break;
	}
}