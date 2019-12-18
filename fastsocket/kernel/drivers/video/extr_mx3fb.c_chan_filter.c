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
struct mx3fb_platform_data {int /*<<< orphan*/  dma_dev; } ;
struct dma_chan_request {scalar_t__ id; TYPE_1__* mx3fb; } ;
struct dma_chan {scalar_t__ chan_id; TYPE_2__* device; } ;
struct device {struct mx3fb_platform_data* platform_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */

__attribute__((used)) static bool chan_filter(struct dma_chan *chan, void *arg)
{
	struct dma_chan_request *rq = arg;
	struct device *dev;
	struct mx3fb_platform_data *mx3fb_pdata;

	if (!rq)
		return false;

	dev = rq->mx3fb->dev;
	mx3fb_pdata = dev->platform_data;

	return rq->id == chan->chan_id &&
		mx3fb_pdata->dma_dev == chan->device->dev;
}