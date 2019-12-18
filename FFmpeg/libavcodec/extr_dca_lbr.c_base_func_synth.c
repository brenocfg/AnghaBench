#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int group_sf ;
struct TYPE_4__ {int framenum; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  synth_tones (TYPE_1__*,int,float*,int,int,int) ; 

__attribute__((used)) static void base_func_synth(DCALbrDecoder *s, int ch, float *values, int sf)
{
    int group;

    // Tonal vs residual shift is 22 subframes
    for (group = 0; group < 5; group++) {
        int group_sf = (s->framenum << group) + ((sf - 22) >> (5 - group));
        int synth_idx = ((((sf - 22) & 31) << group) & 31) + (1 << group) - 1;

        synth_tones(s, ch, values, group, (group_sf - 1) & 31, 30 - synth_idx);
        synth_tones(s, ch, values, group, (group_sf    ) & 31,      synth_idx);
    }
}