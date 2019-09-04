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
struct ws_interval {int next; scalar_t__ ts_start; scalar_t__ ts_end; int /*<<< orphan*/  amp0; int /*<<< orphan*/  amp; int /*<<< orphan*/  dphi0; int /*<<< orphan*/  dphi; int /*<<< orphan*/  phi0; int /*<<< orphan*/  phi; } ;
struct wavesynth_context {int cur_inter; int next_inter; int nb_inter; scalar_t__ next_ts; struct ws_interval* inter; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ INF_TS ; 

__attribute__((used)) static void wavesynth_enter_intervals(struct wavesynth_context *ws, int64_t ts)
{
    int *last, i;
    struct ws_interval *in;

    last = &ws->cur_inter;
    for (i = ws->cur_inter; i >= 0; i = ws->inter[i].next)
        last = &ws->inter[i].next;
    for (i = ws->next_inter; i < ws->nb_inter; i++) {
        in = &ws->inter[i];
        if (ts < in->ts_start)
            break;
        if (ts >= in->ts_end)
            continue;
        *last = i;
        last = &in->next;
        in->phi = in->phi0;
        in->dphi = in->dphi0;
        in->amp = in->amp0;
    }
    ws->next_inter = i;
    ws->next_ts = i < ws->nb_inter ? ws->inter[i].ts_start : INF_TS;
    *last = -1;
}