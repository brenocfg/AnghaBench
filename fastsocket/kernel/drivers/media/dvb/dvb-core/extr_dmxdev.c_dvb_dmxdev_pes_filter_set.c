#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;
struct TYPE_6__ {TYPE_2__ pes; } ;
struct TYPE_4__ {int /*<<< orphan*/  ts; } ;
struct dmxdev_filter {TYPE_3__ params; TYPE_1__ feed; int /*<<< orphan*/  type; } ;
struct dmxdev {int dummy; } ;
struct dmx_pes_filter_params {scalar_t__ pes_type; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMXDEV_STATE_SET ; 
 int /*<<< orphan*/  DMXDEV_TYPE_PES ; 
 int DMX_IMMEDIATE_START ; 
 scalar_t__ DMX_PES_OTHER ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int dvb_dmxdev_add_pid (struct dmxdev*,struct dmxdev_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_reset (struct dmxdev_filter*) ; 
 int dvb_dmxdev_filter_start (struct dmxdev_filter*) ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_state_set (struct dmxdev_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_stop (struct dmxdev_filter*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct dmx_pes_filter_params*,int) ; 

__attribute__((used)) static int dvb_dmxdev_pes_filter_set(struct dmxdev *dmxdev,
				     struct dmxdev_filter *dmxdevfilter,
				     struct dmx_pes_filter_params *params)
{
	int ret;

	dvb_dmxdev_filter_stop(dmxdevfilter);
	dvb_dmxdev_filter_reset(dmxdevfilter);

	if (params->pes_type > DMX_PES_OTHER || params->pes_type < 0)
		return -EINVAL;

	dmxdevfilter->type = DMXDEV_TYPE_PES;
	memcpy(&dmxdevfilter->params, params,
	       sizeof(struct dmx_pes_filter_params));
	INIT_LIST_HEAD(&dmxdevfilter->feed.ts);

	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_SET);

	ret = dvb_dmxdev_add_pid(dmxdev, dmxdevfilter,
				 dmxdevfilter->params.pes.pid);
	if (ret < 0)
		return ret;

	if (params->flags & DMX_IMMEDIATE_START)
		return dvb_dmxdev_filter_start(dmxdevfilter);

	return 0;
}