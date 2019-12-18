#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dmxdev_filter {scalar_t__ state; scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMXDEV_STATE_ALLOCATED ; 
 scalar_t__ DMXDEV_STATE_SET ; 
 scalar_t__ DMXDEV_TYPE_NONE ; 
 scalar_t__ DMXDEV_TYPE_PES ; 
 int /*<<< orphan*/  dvb_dmxdev_delete_pids (struct dmxdev_filter*) ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_state_set (struct dmxdev_filter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int dvb_dmxdev_filter_reset(struct dmxdev_filter *dmxdevfilter)
{
	if (dmxdevfilter->state < DMXDEV_STATE_SET)
		return 0;

	if (dmxdevfilter->type == DMXDEV_TYPE_PES)
		dvb_dmxdev_delete_pids(dmxdevfilter);

	dmxdevfilter->type = DMXDEV_TYPE_NONE;
	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_ALLOCATED);
	return 0;
}