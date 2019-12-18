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
struct dvb_demux_feed {struct dvb_demux* demux; } ;
struct dvb_demux {scalar_t__ priv; } ;
struct budget {scalar_t__ feeding; int /*<<< orphan*/  feedlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,struct budget*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stop_ts_capture (struct budget*) ; 

__attribute__((used)) static int budget_stop_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux = feed->demux;
	struct budget *budget = (struct budget *) demux->priv;
	int status = 0;

	dprintk(2, "budget: %p\n", budget);

	spin_lock(&budget->feedlock);
	if (--budget->feeding == 0)
		status = stop_ts_capture(budget);
	spin_unlock(&budget->feedlock);
	return status;
}