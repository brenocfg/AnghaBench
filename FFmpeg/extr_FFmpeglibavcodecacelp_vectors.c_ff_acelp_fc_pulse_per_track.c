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
typedef  int uint8_t ;
typedef  int int16_t ;

/* Variables and functions */

void ff_acelp_fc_pulse_per_track(
        int16_t* fc_v,
        const uint8_t *tab1,
        const uint8_t *tab2,
        int pulse_indexes,
        int pulse_signs,
        int pulse_count,
        int bits)
{
    int mask = (1 << bits) - 1;
    int i;

    for(i=0; i<pulse_count; i++)
    {
        fc_v[i + tab1[pulse_indexes & mask]] +=
                (pulse_signs & 1) ? 8191 : -8192; // +/-1 in (2.13)

        pulse_indexes >>= bits;
        pulse_signs >>= 1;
    }

    fc_v[tab2[pulse_indexes]] += (pulse_signs & 1) ? 8191 : -8192;
}