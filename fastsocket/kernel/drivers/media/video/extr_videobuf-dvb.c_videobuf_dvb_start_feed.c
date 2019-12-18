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
struct videobuf_dvb {int nfeeds; int /*<<< orphan*/  lock; int /*<<< orphan*/ * thread; int /*<<< orphan*/  name; } ;
struct dvb_demux_feed {struct dvb_demux* demux; } ;
struct TYPE_2__ {int /*<<< orphan*/  frontend; } ;
struct dvb_demux {TYPE_1__ dmx; struct videobuf_dvb* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct videobuf_dvb*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_dvb_thread ; 

__attribute__((used)) static int videobuf_dvb_start_feed(struct dvb_demux_feed *feed)
{
	struct dvb_demux *demux  = feed->demux;
	struct videobuf_dvb *dvb = demux->priv;
	int rc;

	if (!demux->dmx.frontend)
		return -EINVAL;

	mutex_lock(&dvb->lock);
	dvb->nfeeds++;
	rc = dvb->nfeeds;

	if (NULL != dvb->thread)
		goto out;
	dvb->thread = kthread_run(videobuf_dvb_thread,
				  dvb, "%s dvb", dvb->name);
	if (IS_ERR(dvb->thread)) {
		rc = PTR_ERR(dvb->thread);
		dvb->thread = NULL;
	}

out:
	mutex_unlock(&dvb->lock);
	return rc;
}