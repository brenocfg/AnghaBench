#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dvb_demux_feed {scalar_t__ pusi_seen; struct dvb_demux* demux; } ;
struct TYPE_2__ {int /*<<< orphan*/  frontend; } ;
struct dvb_demux {TYPE_1__ dmx; scalar_t__ priv; } ;
struct budget {int /*<<< orphan*/  feedlock; int /*<<< orphan*/  feeding; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*,struct budget*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int start_ts_capture (struct budget*) ; 

__attribute__((used)) static int budget_start_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct budget *budget = (struct budget *) demux->priv;
	int status = 0;

	dprintk(2, "budget: %p\n", budget);

	if (!demux->dmx.frontend)
		return -EINVAL;

	spin_lock(&budget->feedlock);
	feed->pusi_seen = 0; /* have a clean section start */
	if (budget->feeding++ == 0)
		status = start_ts_capture(budget);
	spin_unlock(&budget->feedlock);
	return status;
}