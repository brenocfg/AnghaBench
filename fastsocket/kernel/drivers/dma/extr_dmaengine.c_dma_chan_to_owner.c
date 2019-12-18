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
struct module {int dummy; } ;
struct dma_chan {TYPE_3__* device; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_4__ {struct module* owner; } ;

/* Variables and functions */

__attribute__((used)) static struct module *dma_chan_to_owner(struct dma_chan *chan)
{
	return chan->device->dev->driver->owner;
}