#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  removed ;
struct TYPE_11__ {int /*<<< orphan*/  srcref; } ;
typedef  TYPE_2__ nstat_src ;
struct TYPE_10__ {int length; scalar_t__ context; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {int /*<<< orphan*/  srcref; TYPE_1__ hdr; } ;
typedef  TYPE_3__ nstat_msg_src_removed ;
struct TYPE_13__ {int /*<<< orphan*/  ncs_unit; int /*<<< orphan*/  ncs_kctl; } ;
typedef  TYPE_4__ nstat_control_state ;
typedef  scalar_t__ errno_t ;
struct TYPE_14__ {int nstat_msgremovedfailures; } ;

/* Variables and functions */
 int CTL_DATA_CRIT ; 
 int CTL_DATA_EOR ; 
 int /*<<< orphan*/  NSTAT_MSG_TYPE_SRC_REMOVED ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 scalar_t__ ctl_enqueuedata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int,int) ; 
 TYPE_5__ nstat_stats ; 

__attribute__((used)) static errno_t
nstat_control_send_removed(
	nstat_control_state	*state,
	nstat_src		*src)
{
	nstat_msg_src_removed removed;
	errno_t result;

	bzero(&removed, sizeof(removed));
	removed.hdr.type = NSTAT_MSG_TYPE_SRC_REMOVED;
	removed.hdr.length = sizeof(removed);
	removed.hdr.context = 0;
	removed.srcref = src->srcref;
	result = ctl_enqueuedata(state->ncs_kctl, state->ncs_unit, &removed,
	    sizeof(removed), CTL_DATA_EOR | CTL_DATA_CRIT);
	if (result != 0)
		nstat_stats.nstat_msgremovedfailures += 1;

	return result;
}