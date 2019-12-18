#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {struct TYPE_15__* ce; } ;
struct TYPE_13__ {int low; } ;
struct TYPE_12__ {scalar_t__ ringback; scalar_t__ busytone; scalar_t__ dialtone; } ;
struct TYPE_14__ {int play_mode; int rec_mode; TYPE_2__ dsp; TYPE_4__* cadence_t; scalar_t__ tone_cadence_state; scalar_t__ tone_state; TYPE_1__ flags; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  idle (TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_play_start (TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_play_tone (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixj_record_start (TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_set_tone_off (int,TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_set_tone_on (int,TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 

__attribute__((used)) static void ixj_cpt_stop(IXJ *j)
{
	if(j->tone_state || j->tone_cadence_state)
	{
		j->flags.dialtone = 0;
		j->flags.busytone = 0;
		j->flags.ringback = 0;
		ixj_set_tone_on(0x0001, j);
		ixj_set_tone_off(0x0000, j);
		ixj_play_tone(j, 0);
		j->tone_state = j->tone_cadence_state = 0;
		if (j->cadence_t) {
			kfree(j->cadence_t->ce);
			kfree(j->cadence_t);
			j->cadence_t = NULL;
		}
	}
	if (j->play_mode == -1 && j->rec_mode == -1)
		idle(j);
	if (j->play_mode != -1 && j->dsp.low == 0x20)
		ixj_play_start(j);
	if (j->rec_mode != -1 && j->dsp.low == 0x20)
		ixj_record_start(j);
}