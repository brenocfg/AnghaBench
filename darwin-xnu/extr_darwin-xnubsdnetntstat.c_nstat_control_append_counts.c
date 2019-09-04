#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int filter; int /*<<< orphan*/  cookie; TYPE_1__* provider; int /*<<< orphan*/  srcref; } ;
typedef  TYPE_2__ nstat_src ;
struct TYPE_12__ {int length; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {scalar_t__ nstat_rxbytes; scalar_t__ nstat_txbytes; } ;
struct TYPE_10__ {TYPE_6__ hdr; TYPE_4__ counts; scalar_t__ event_flags; int /*<<< orphan*/  srcref; } ;
typedef  TYPE_3__ nstat_msg_src_counts ;
typedef  int /*<<< orphan*/  nstat_control_state ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  counts ;
struct TYPE_8__ {scalar_t__ (* nstat_counts ) (int /*<<< orphan*/ ,TYPE_4__*,int*) ;} ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int NSTAT_FILTER_NOZEROBYTES ; 
 int /*<<< orphan*/  NSTAT_MSG_TYPE_SRC_COUNTS ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 scalar_t__ nstat_accumulate_msg (int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_4__*,int*) ; 

__attribute__((used)) static errno_t
nstat_control_append_counts(
	nstat_control_state	*state,
	nstat_src			*src,
	int					*gone)
{
	/* Some providers may not have any counts to send */
	if (!src->provider->nstat_counts) return 0;

	nstat_msg_src_counts counts;
	bzero(&counts, sizeof(counts));
	counts.hdr.type = NSTAT_MSG_TYPE_SRC_COUNTS;
	counts.hdr.length = sizeof(counts);
	counts.srcref = src->srcref;
	counts.event_flags = 0;

	errno_t	result = 0;
	result = src->provider->nstat_counts(src->cookie, &counts.counts, gone);
	if (result != 0)
	{
		return result;
	}

	if ((src->filter & NSTAT_FILTER_NOZEROBYTES) == NSTAT_FILTER_NOZEROBYTES &&
		counts.counts.nstat_rxbytes == 0 && counts.counts.nstat_txbytes == 0)
	{
		return EAGAIN;
	}

	return nstat_accumulate_msg(state, &counts.hdr, counts.hdr.length);
}