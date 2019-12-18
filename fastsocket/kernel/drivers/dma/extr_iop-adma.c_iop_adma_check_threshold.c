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
struct iop_adma_chan {scalar_t__ pending; TYPE_2__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ IOP_ADMA_THRESHOLD ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  iop_chan_append (struct iop_adma_chan*) ; 

__attribute__((used)) static void iop_adma_check_threshold(struct iop_adma_chan *iop_chan)
{
	dev_dbg(iop_chan->device->common.dev, "pending: %d\n",
		iop_chan->pending);

	if (iop_chan->pending >= IOP_ADMA_THRESHOLD) {
		iop_chan->pending = 0;
		iop_chan_append(iop_chan);
	}
}