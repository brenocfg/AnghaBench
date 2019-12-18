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
struct pd_dvb_adapter {int /*<<< orphan*/  active_feed; } ;
struct dvb_demux_feed {TYPE_1__* demux; } ;
struct TYPE_2__ {struct pd_dvb_adapter* priv; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_stop_streaming (struct pd_dvb_adapter*) ; 

__attribute__((used)) static int pd_stop_feed(struct dvb_demux_feed *feed)
{
	struct pd_dvb_adapter *pd_dvb = feed->demux->priv;

	if (!pd_dvb)
		return -1;
	if (atomic_dec_and_test(&pd_dvb->active_feed))
		dvb_stop_streaming(pd_dvb);
	return 0;
}