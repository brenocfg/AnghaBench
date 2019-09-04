#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ws_intervals {int /*<<< orphan*/  nb_inter; } ;
struct TYPE_4__ {scalar_t__ slide; } ;
struct sbg_script_event {int ts; int ts_int; int ts_trans; int ts_next; TYPE_1__ fade; } ;
struct sbg_script {int opt_fade_time; int nb_events; int nb_synth; struct sbg_script_event* events; TYPE_3__* synth; } ;
typedef  int int64_t ;
struct TYPE_5__ {int l; int r; } ;
struct TYPE_6__ {TYPE_2__ ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_TIME_BASE ; 
 int DAY_TS ; 
 void* FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 void* av_rescale (int,int,int /*<<< orphan*/ ) ; 
 int generate_plateau (void*,struct sbg_script*,struct ws_intervals*,struct sbg_script_event*) ; 
 int generate_transition (void*,struct sbg_script*,struct ws_intervals*,struct sbg_script_event*,struct sbg_script_event*) ; 

__attribute__((used)) static int generate_intervals(void *log, struct sbg_script *s, int sample_rate,
                              struct ws_intervals *inter)
{
    int64_t trans_time = s->opt_fade_time / 2;
    struct sbg_script_event ev0, *ev1, *ev2;
    int64_t period;
    int i, r;

    /* SBaGen handles the time before and after the extremal events,
       and the corresponding transitions, as if the sequence were cyclic
       with a 24-hours period. */
    period = s->events[s->nb_events - 1].ts - s->events[0].ts;
    period = (period + (DAY_TS - 1)) / DAY_TS * DAY_TS;
    period = FFMAX(period, DAY_TS);

    /* Prepare timestamps for transitions */
    for (i = 0; i < s->nb_events; i++) {
        ev1 = &s->events[i];
        ev2 = &s->events[(i + 1) % s->nb_events];
        ev1->ts_int   = ev1->ts;
        ev1->ts_trans = ev1->fade.slide ? ev1->ts
                                        : ev2->ts + (ev1 < ev2 ? 0 : period);
    }
    for (i = 0; i < s->nb_events; i++) {
        ev1 = &s->events[i];
        ev2 = &s->events[(i + 1) % s->nb_events];
        if (!ev1->fade.slide) {
            ev1->ts_trans = FFMAX(ev1->ts_int,   ev1->ts_trans - trans_time);
            ev2->ts_int   = FFMIN(ev2->ts_trans, ev2->ts_int   + trans_time);
        }
        ev1->ts_next  = ev2->ts_int + (ev1 < ev2 ? 0 : period);
    }

    /* Pseudo event before the first one */
    ev0 = s->events[s->nb_events - 1];
    ev0.ts_int   -= period;
    ev0.ts_trans -= period;
    ev0.ts_next  -= period;

    /* Convert timestamps */
    for (i = -1; i < s->nb_events; i++) {
        ev1 = i < 0 ? &ev0 : &s->events[i];
        ev1->ts_int   = av_rescale(ev1->ts_int,   sample_rate, AV_TIME_BASE);
        ev1->ts_trans = av_rescale(ev1->ts_trans, sample_rate, AV_TIME_BASE);
        ev1->ts_next  = av_rescale(ev1->ts_next,  sample_rate, AV_TIME_BASE);
    }

    /* Generate intervals */
    for (i = 0; i < s->nb_synth; i++)
        s->synth[i].ref.l = s->synth[i].ref.r = -1;
    for (i = -1; i < s->nb_events; i++) {
        ev1 = i < 0 ? &ev0 : &s->events[i];
        ev2 = &s->events[(i + 1) % s->nb_events];
        r = generate_plateau(log, s, inter, ev1);
        if (r < 0)
            return r;
        r = generate_transition(log, s, inter, ev1, ev2);
        if (r < 0)
            return r;
    }
    if (!inter->nb_inter)
        av_log(log, AV_LOG_WARNING, "Completely silent script.\n");
    return 0;
}