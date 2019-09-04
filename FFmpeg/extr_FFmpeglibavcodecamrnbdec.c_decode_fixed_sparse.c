#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  enum Mode { ____Placeholder_Mode } Mode ;
struct TYPE_5__ {int* x; int n; double* y; } ;
typedef  TYPE_1__ AMRFixed ;

/* Variables and functions */
 int const MODE_10k2 ; 
 int const MODE_12k2 ; 
 int MODE_4k75 ; 
 int const MODE_5k15 ; 
 int const MODE_5k9 ; 
 int const MODE_6k7 ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  decode_8_pulses_31bits (int const*,TYPE_1__*) ; 
 int /*<<< orphan*/  ff_decode_10_pulses_35bits (int const*,TYPE_1__*,int*,int,int) ; 
 int* gray_decode ; 
 int const* track_position ; 

__attribute__((used)) static void decode_fixed_sparse(AMRFixed *fixed_sparse, const uint16_t *pulses,
                                const enum Mode mode, const int subframe)
{
    av_assert1(MODE_4k75 <= (signed)mode && mode <= MODE_12k2);

    if (mode == MODE_12k2) {
        ff_decode_10_pulses_35bits(pulses, fixed_sparse, gray_decode, 5, 3);
    } else if (mode == MODE_10k2) {
        decode_8_pulses_31bits(pulses, fixed_sparse);
    } else {
        int *pulse_position = fixed_sparse->x;
        int i, pulse_subset;
        const int fixed_index = pulses[0];

        if (mode <= MODE_5k15) {
            pulse_subset      = ((fixed_index >> 3) & 8)     + (subframe << 1);
            pulse_position[0] = ( fixed_index       & 7) * 5 + track_position[pulse_subset];
            pulse_position[1] = ((fixed_index >> 3) & 7) * 5 + track_position[pulse_subset + 1];
            fixed_sparse->n = 2;
        } else if (mode == MODE_5k9) {
            pulse_subset      = ((fixed_index & 1) << 1) + 1;
            pulse_position[0] = ((fixed_index >> 1) & 7) * 5 + pulse_subset;
            pulse_subset      = (fixed_index  >> 4) & 3;
            pulse_position[1] = ((fixed_index >> 6) & 7) * 5 + pulse_subset + (pulse_subset == 3 ? 1 : 0);
            fixed_sparse->n = pulse_position[0] == pulse_position[1] ? 1 : 2;
        } else if (mode == MODE_6k7) {
            pulse_position[0] = (fixed_index        & 7) * 5;
            pulse_subset      = (fixed_index  >> 2) & 2;
            pulse_position[1] = ((fixed_index >> 4) & 7) * 5 + pulse_subset + 1;
            pulse_subset      = (fixed_index  >> 6) & 2;
            pulse_position[2] = ((fixed_index >> 8) & 7) * 5 + pulse_subset + 2;
            fixed_sparse->n = 3;
        } else { // mode <= MODE_7k95
            pulse_position[0] = gray_decode[ fixed_index        & 7];
            pulse_position[1] = gray_decode[(fixed_index >> 3)  & 7] + 1;
            pulse_position[2] = gray_decode[(fixed_index >> 6)  & 7] + 2;
            pulse_subset      = (fixed_index >> 9) & 1;
            pulse_position[3] = gray_decode[(fixed_index >> 10) & 7] + pulse_subset + 3;
            fixed_sparse->n = 4;
        }
        for (i = 0; i < fixed_sparse->n; i++)
            fixed_sparse->y[i] = (pulses[1] >> i) & 1 ? 1.0 : -1.0;
    }
}