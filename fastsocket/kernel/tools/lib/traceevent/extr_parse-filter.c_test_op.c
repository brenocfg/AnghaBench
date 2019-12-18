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
struct pevent_record {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct filter_arg {TYPE_1__ op; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
#define  FILTER_OP_AND 130 
#define  FILTER_OP_NOT 129 
#define  FILTER_OP_OR 128 
 int /*<<< orphan*/  test_filter (struct event_format*,int /*<<< orphan*/ ,struct pevent_record*) ; 

__attribute__((used)) static int test_op(struct event_format *event,
		   struct filter_arg *arg, struct pevent_record *record)
{
	switch (arg->op.type) {
	case FILTER_OP_AND:
		return test_filter(event, arg->op.left, record) &&
			test_filter(event, arg->op.right, record);

	case FILTER_OP_OR:
		return test_filter(event, arg->op.left, record) ||
			test_filter(event, arg->op.right, record);

	case FILTER_OP_NOT:
		return !test_filter(event, arg->op.right, record);

	default:
		/* ?? */
		return 0;
	}
}