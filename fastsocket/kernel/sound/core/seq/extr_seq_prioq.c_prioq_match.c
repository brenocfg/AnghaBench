#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {TYPE_1__ time; int /*<<< orphan*/  tick; } ;
struct TYPE_8__ {int client; } ;
struct TYPE_7__ {int client; } ;
struct TYPE_9__ {int flags; TYPE_5__ time; TYPE_3__ dest; TYPE_2__ source; } ;
struct snd_seq_event_cell {TYPE_4__ event; } ;

/* Variables and functions */
 int SNDRV_SEQ_TIME_STAMP_MASK ; 
#define  SNDRV_SEQ_TIME_STAMP_REAL 129 
#define  SNDRV_SEQ_TIME_STAMP_TICK 128 

__attribute__((used)) static inline int prioq_match(struct snd_seq_event_cell *cell,
			      int client, int timestamp)
{
	if (cell->event.source.client == client ||
	    cell->event.dest.client == client)
		return 1;
	if (!timestamp)
		return 0;
	switch (cell->event.flags & SNDRV_SEQ_TIME_STAMP_MASK) {
	case SNDRV_SEQ_TIME_STAMP_TICK:
		if (cell->event.time.tick)
			return 1;
		break;
	case SNDRV_SEQ_TIME_STAMP_REAL:
		if (cell->event.time.time.tv_sec ||
		    cell->event.time.time.tv_nsec)
			return 1;
		break;
	}
	return 0;
}