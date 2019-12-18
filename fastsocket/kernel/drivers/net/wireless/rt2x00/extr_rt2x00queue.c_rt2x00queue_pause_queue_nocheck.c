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
struct data_queue {int qid; TYPE_1__* rt2x00dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
#define  QID_AC_BE 131 
#define  QID_AC_BK 130 
#define  QID_AC_VI 129 
#define  QID_AC_VO 128 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,int) ; 

void rt2x00queue_pause_queue_nocheck(struct data_queue *queue)
{
	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		/*
		 * For TX queues, we have to disable the queue
		 * inside mac80211.
		 */
		ieee80211_stop_queue(queue->rt2x00dev->hw, queue->qid);
		break;
	default:
		break;
	}
}