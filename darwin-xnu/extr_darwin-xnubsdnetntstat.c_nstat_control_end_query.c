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
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  nstat_src ;
struct TYPE_3__ {scalar_t__ ncs_context; } ;
typedef  TYPE_1__ nstat_control_state ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  NSTAT_MSG_HDR_FLAG_CONTINUATION ; 

__attribute__((used)) static u_int16_t
nstat_control_end_query(
    nstat_control_state *state,
    nstat_src *last_src,
    boolean_t partial)
{
	u_int16_t flags = 0;

	if (last_src == NULL || !partial)
	{
		/*
		 * We iterated through the entire srcs list or exited early
		 * from the loop when a partial update was not requested (an
		 * error occurred), so clear context to indicate internally
		 * that the query is finished.
		 */
		state->ncs_context = 0;
	}
	else
	{
		/*
		 * Indicate to userlevel to make another partial request as
		 * there are still sources left to be reported.
		 */
		flags |= NSTAT_MSG_HDR_FLAG_CONTINUATION;
	}

	return flags;
}