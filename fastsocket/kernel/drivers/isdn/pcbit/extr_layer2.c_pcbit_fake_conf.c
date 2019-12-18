#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcbit_dev {TYPE_1__* dev_if; int /*<<< orphan*/  id; } ;
struct pcbit_chan {int /*<<< orphan*/  id; scalar_t__ queued; } ;
struct TYPE_5__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  command; int /*<<< orphan*/  driver; } ;
typedef  TYPE_2__ isdn_ctrl ;
struct TYPE_4__ {int /*<<< orphan*/  (* statcallb ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISDN_STAT_BSENT ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static __inline__ void
pcbit_fake_conf(struct pcbit_dev *dev, struct pcbit_chan *chan)
{
	isdn_ctrl ictl;

	if (chan->queued) {
		chan->queued--;

		ictl.driver = dev->id;
		ictl.command = ISDN_STAT_BSENT;
		ictl.arg = chan->id;
		dev->dev_if->statcallb(&ictl);
	}
}