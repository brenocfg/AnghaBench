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
struct pcbit_dev {struct pcbit_chan* b2; struct pcbit_chan* b1; } ;
struct pcbit_chan {scalar_t__ fsm_state; } ;

/* Variables and functions */
 scalar_t__ ST_ACTIVE ; 
 int /*<<< orphan*/  pcbit_fake_conf (struct pcbit_dev*,struct pcbit_chan*) ; 

__attribute__((used)) static void
pcbit_firmware_bug(struct pcbit_dev *dev)
{
	struct pcbit_chan *chan;

	chan = dev->b1;

	if (chan->fsm_state == ST_ACTIVE) {
		pcbit_fake_conf(dev, chan);
	}
	chan = dev->b2;

	if (chan->fsm_state == ST_ACTIVE) {
		pcbit_fake_conf(dev, chan);
	}
}