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
struct dumchannel_uf {int channelnr; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y_offset; int /*<<< orphan*/  x_offset; int /*<<< orphan*/  source; int /*<<< orphan*/  dirty; } ;
struct TYPE_4__ {int* fb_owning_channel; TYPE_1__* chan_uf_store; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y_offset; int /*<<< orphan*/  x_offset; int /*<<< orphan*/  source; int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 int EFBNOTOWNER ; 
 int EINVAL ; 
 int MAX_DUM_CHANNELS ; 
 int display_open (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ dum_data ; 

int pnx4008_put_dum_channel_uf(struct dumchannel_uf chan_uf, int dev_id)
{
	int i = chan_uf.channelnr;
	int ret;

	if (i < 0 || i > MAX_DUM_CHANNELS)
		return -EINVAL;
	else if (dum_data.fb_owning_channel[i] != dev_id)
		return -EFBNOTOWNER;
	else if ((ret =
		  display_open(chan_uf.channelnr, 0, chan_uf.dirty,
			       chan_uf.source, chan_uf.y_offset,
			       chan_uf.x_offset, chan_uf.height,
			       chan_uf.width)) != 0)
		return ret;
	else {
		dum_data.chan_uf_store[i].dirty = chan_uf.dirty;
		dum_data.chan_uf_store[i].source = chan_uf.source;
		dum_data.chan_uf_store[i].x_offset = chan_uf.x_offset;
		dum_data.chan_uf_store[i].y_offset = chan_uf.y_offset;
		dum_data.chan_uf_store[i].width = chan_uf.width;
		dum_data.chan_uf_store[i].height = chan_uf.height;
	}

	return 0;
}