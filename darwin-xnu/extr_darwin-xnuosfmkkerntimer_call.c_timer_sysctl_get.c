#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int interval; int scans; int preempts; int latency; int latency_min; int latency_max; } ;
struct TYPE_6__ {int count; } ;
struct TYPE_7__ {int enqueues; int dequeues; int escalates; int scan_limit; int scan_interval; int scan_pauses; TYPE_1__ threshold; TYPE_2__ queue; } ;
typedef  TYPE_3__ timer_longterm_t ;

/* Variables and functions */
#define  DEQUEUES 140 
#define  ENQUEUES 139 
#define  ESCALATES 138 
#define  LATENCY 137 
#define  LATENCY_MAX 136 
#define  LATENCY_MIN 135 
 int NSEC_PER_MSEC ; 
#define  PAUSES 134 
#define  PREEMPTS 133 
#define  QCOUNT 132 
#define  SCANS 131 
#define  SCAN_INTERVAL 130 
#define  SCAN_LIMIT 129 
#define  THRESHOLD 128 
 int TIMER_LONGTERM_NONE ; 
 TYPE_3__ timer_longterm ; 

uint64_t
timer_sysctl_get(int oid)
{
	timer_longterm_t	*tlp = &timer_longterm;

	switch (oid) {
	case THRESHOLD:
		return (tlp->threshold.interval == TIMER_LONGTERM_NONE) ?
			0 : tlp->threshold.interval / NSEC_PER_MSEC;
	case QCOUNT:
		return tlp->queue.count;
	case ENQUEUES:
		return tlp->enqueues;
	case DEQUEUES:
		return tlp->dequeues;
	case ESCALATES:
		return tlp->escalates;
	case SCANS:
		return tlp->threshold.scans;
	case PREEMPTS:
		return tlp->threshold.preempts;
	case LATENCY:
		return tlp->threshold.latency;
	case LATENCY_MIN:
		return tlp->threshold.latency_min;
	case LATENCY_MAX:
		return tlp->threshold.latency_max;
	case SCAN_LIMIT:
		return tlp->scan_limit;
	case SCAN_INTERVAL:
		return tlp->scan_interval;
	case PAUSES:
		return tlp->scan_pauses;
	default:
		return 0;
	}
}