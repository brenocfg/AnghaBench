#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float* max_persistent; scalar_t__* nb_frames_max_display; scalar_t__ persistent_max_frames; } ;
typedef  TYPE_1__ ShowVolumeContext ;

/* Variables and functions */

__attribute__((used)) static inline void calc_persistent_max(ShowVolumeContext *s, float max, int channel)
{
    /* update max value for persistent max display */
    if ((max >= s->max_persistent[channel]) || (s->nb_frames_max_display[channel] >= s->persistent_max_frames)) { /* update max value for display */
        s->max_persistent[channel] = max;
        s->nb_frames_max_display[channel] = 0;
    } else {
        s->nb_frames_max_display[channel] += 1; /* incremente display frame count */
    }
}