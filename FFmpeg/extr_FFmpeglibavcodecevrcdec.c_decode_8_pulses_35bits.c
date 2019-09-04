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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void decode_8_pulses_35bits(const uint16_t *fixed_index, float *cod)
{
    int i, pos1, pos2, offset;

    offset = (fixed_index[3] >> 9) & 3;

    for (i = 0; i < 3; i++) {
        pos1 = ((fixed_index[i] & 0x7f) / 11) * 5 + ((i + offset) % 5);
        pos2 = ((fixed_index[i] & 0x7f) % 11) * 5 + ((i + offset) % 5);

        cod[pos1] = (fixed_index[i] & 0x80) ? -1.0 : 1.0;

        if (pos2 < pos1)
            cod[pos2]  = -cod[pos1];
        else
            cod[pos2] +=  cod[pos1];
    }

    pos1 = ((fixed_index[3] & 0x7f) / 11) * 5 + ((3 + offset) % 5);
    pos2 = ((fixed_index[3] & 0x7f) % 11) * 5 + ((4 + offset) % 5);

    cod[pos1] = (fixed_index[3] & 0x100) ? -1.0 : 1.0;
    cod[pos2] = (fixed_index[3] & 0x80 ) ? -1.0 : 1.0;
}