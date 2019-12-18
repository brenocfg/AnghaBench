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
struct TYPE_15__ {int tone_state; size_t tone_cadence_state; TYPE_2__* cadence_t; } ;
struct TYPE_14__ {int /*<<< orphan*/  gain1; int /*<<< orphan*/  freq1; scalar_t__ gain0; int /*<<< orphan*/  freq0; int /*<<< orphan*/  tone_index; } ;
struct TYPE_13__ {size_t elements_used; int termination; TYPE_1__* ce; } ;
struct TYPE_12__ {int /*<<< orphan*/  index; int /*<<< orphan*/  tone_off_time; int /*<<< orphan*/  tone_on_time; int /*<<< orphan*/  gain1; int /*<<< orphan*/  freq1; scalar_t__ gain0; int /*<<< orphan*/  freq0; } ;
typedef  TYPE_3__ IXJ_TONE ;
typedef  TYPE_4__ IXJ ;

/* Variables and functions */
#define  PLAY_ONCE 130 
#define  REPEAT_ALL 129 
#define  REPEAT_LAST_ELEMENT 128 
 int /*<<< orphan*/  ixj_cpt_stop (TYPE_4__*) ; 
 int /*<<< orphan*/  ixj_init_tone (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ixj_play_tone (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixj_set_tone_off (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ixj_set_tone_on (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void ixj_tone_timeout(IXJ *j)
{
	IXJ_TONE ti;

	j->tone_state++;
	if (j->tone_state == 3) {
		j->tone_state = 0;
		if (j->cadence_t) {
			j->tone_cadence_state++;
			if (j->tone_cadence_state >= j->cadence_t->elements_used) {
				switch (j->cadence_t->termination) {
				case PLAY_ONCE:
					ixj_cpt_stop(j);
					break;
				case REPEAT_LAST_ELEMENT:
					j->tone_cadence_state--;
					ixj_play_tone(j, j->cadence_t->ce[j->tone_cadence_state].index);
					break;
				case REPEAT_ALL:
					j->tone_cadence_state = 0;
					if (j->cadence_t->ce[j->tone_cadence_state].freq0) {
						ti.tone_index = j->cadence_t->ce[j->tone_cadence_state].index;
						ti.freq0 = j->cadence_t->ce[j->tone_cadence_state].freq0;
						ti.gain0 = j->cadence_t->ce[j->tone_cadence_state].gain0;
						ti.freq1 = j->cadence_t->ce[j->tone_cadence_state].freq1;
						ti.gain1 = j->cadence_t->ce[j->tone_cadence_state].gain1;
						ixj_init_tone(j, &ti);
					}
					ixj_set_tone_on(j->cadence_t->ce[0].tone_on_time, j);
					ixj_set_tone_off(j->cadence_t->ce[0].tone_off_time, j);
					ixj_play_tone(j, j->cadence_t->ce[0].index);
					break;
				}
			} else {
				if (j->cadence_t->ce[j->tone_cadence_state].gain0) {
					ti.tone_index = j->cadence_t->ce[j->tone_cadence_state].index;
					ti.freq0 = j->cadence_t->ce[j->tone_cadence_state].freq0;
					ti.gain0 = j->cadence_t->ce[j->tone_cadence_state].gain0;
					ti.freq1 = j->cadence_t->ce[j->tone_cadence_state].freq1;
					ti.gain1 = j->cadence_t->ce[j->tone_cadence_state].gain1;
					ixj_init_tone(j, &ti);
				}
				ixj_set_tone_on(j->cadence_t->ce[j->tone_cadence_state].tone_on_time, j);
				ixj_set_tone_off(j->cadence_t->ce[j->tone_cadence_state].tone_off_time, j);
				ixj_play_tone(j, j->cadence_t->ce[j->tone_cadence_state].index);
			}
		}
	}
}