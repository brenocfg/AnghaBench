#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_12__ {int /*<<< orphan*/  sec; } ;
struct TYPE_8__ {scalar_t__ pid; } ;
struct TYPE_9__ {TYPE_1__ sec; } ;
struct dmxdev_filter {TYPE_5__ feed; struct dmxdev* dev; TYPE_2__ params; } ;
struct dmxdev {int filternum; TYPE_6__* demux; TYPE_7__* filter; } ;
struct TYPE_10__ {scalar_t__ pid; } ;
struct TYPE_11__ {TYPE_3__ sec; } ;
struct TYPE_14__ {scalar_t__ state; scalar_t__ type; TYPE_4__ params; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* release_section_feed ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ DMXDEV_STATE_GO ; 
 scalar_t__ DMXDEV_TYPE_SEC ; 
 int /*<<< orphan*/  dvb_dmxdev_feed_start (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dvb_dmxdev_feed_restart(struct dmxdev_filter *filter)
{
	int i;
	struct dmxdev *dmxdev = filter->dev;
	u16 pid = filter->params.sec.pid;

	for (i = 0; i < dmxdev->filternum; i++)
		if (dmxdev->filter[i].state >= DMXDEV_STATE_GO &&
		    dmxdev->filter[i].type == DMXDEV_TYPE_SEC &&
		    dmxdev->filter[i].params.sec.pid == pid) {
			dvb_dmxdev_feed_start(&dmxdev->filter[i]);
			return 0;
		}

	filter->dev->demux->release_section_feed(dmxdev->demux,
						 filter->feed.sec);

	return 0;
}