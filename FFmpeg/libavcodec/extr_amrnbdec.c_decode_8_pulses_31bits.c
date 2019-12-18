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
typedef  int int16_t ;
struct TYPE_3__ {int n; int* x; float* y; } ;
typedef  TYPE_1__ AMRFixed ;

/* Variables and functions */
 int /*<<< orphan*/  decode_10bit_pulse (int const,int*,int,int,int) ; 

__attribute__((used)) static void decode_8_pulses_31bits(const int16_t *fixed_index,
                                   AMRFixed *fixed_sparse)
{
    int pulse_position[8];
    int i, temp;

    decode_10bit_pulse(fixed_index[4], pulse_position, 0, 4, 1);
    decode_10bit_pulse(fixed_index[5], pulse_position, 2, 6, 5);

    // coded using 5+2 bits with the 2 LSBs being, individually, the LSB of 1 of
    // the 2 pulses and the upper 5 bits being coded in base 5
    temp = ((fixed_index[6] >> 2) * 25 + 12) >> 5;
    pulse_position[3] = temp % 5;
    pulse_position[7] = temp / 5;
    if (pulse_position[7] & 1)
        pulse_position[3] = 4 - pulse_position[3];
    pulse_position[3] = (pulse_position[3] << 1) + ( fixed_index[6]       & 1);
    pulse_position[7] = (pulse_position[7] << 1) + ((fixed_index[6] >> 1) & 1);

    fixed_sparse->n = 8;
    for (i = 0; i < 4; i++) {
        const int pos1   = (pulse_position[i]     << 2) + i;
        const int pos2   = (pulse_position[i + 4] << 2) + i;
        const float sign = fixed_index[i] ? -1.0 : 1.0;
        fixed_sparse->x[i    ] = pos1;
        fixed_sparse->x[i + 4] = pos2;
        fixed_sparse->y[i    ] = sign;
        fixed_sparse->y[i + 4] = pos2 < pos1 ? -sign : sign;
    }
}