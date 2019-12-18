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
typedef  scalar_t__ uint16_t ;
typedef  enum Mode { ____Placeholder_Mode } Mode ;

/* Variables and functions */
 int AMRWB_SFR_SIZE ; 
 int FFABS (int) ; 
#define  MODE_12k65 136 
#define  MODE_14k25 135 
#define  MODE_15k85 134 
#define  MODE_18k25 133 
#define  MODE_19k85 132 
#define  MODE_23k05 131 
#define  MODE_23k85 130 
#define  MODE_6k60 129 
#define  MODE_8k85 128 
 int /*<<< orphan*/  decode_1p_track (int*,scalar_t__ const,int,int) ; 
 int /*<<< orphan*/  decode_2p_track (int*,scalar_t__ const,int,int) ; 
 int /*<<< orphan*/  decode_3p_track (int*,scalar_t__ const,int,int) ; 
 int /*<<< orphan*/  decode_4p_track (int*,int,int,int) ; 
 int /*<<< orphan*/  decode_5p_track (int*,int,int,int) ; 
 int /*<<< orphan*/  decode_6p_track (int*,int,int,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int** pulses_nb_per_mode_tr ; 

__attribute__((used)) static void decode_fixed_vector(float *fixed_vector, const uint16_t *pulse_hi,
                                const uint16_t *pulse_lo, const enum Mode mode)
{
    /* sig_pos stores for each track the decoded pulse position indexes
     * (1-based) multiplied by its corresponding amplitude (+1 or -1) */
    int sig_pos[4][6];
    int spacing = (mode == MODE_6k60) ? 2 : 4;
    int i, j;

    switch (mode) {
    case MODE_6k60:
        for (i = 0; i < 2; i++)
            decode_1p_track(sig_pos[i], pulse_lo[i], 5, 1);
        break;
    case MODE_8k85:
        for (i = 0; i < 4; i++)
            decode_1p_track(sig_pos[i], pulse_lo[i], 4, 1);
        break;
    case MODE_12k65:
        for (i = 0; i < 4; i++)
            decode_2p_track(sig_pos[i], pulse_lo[i], 4, 1);
        break;
    case MODE_14k25:
        for (i = 0; i < 2; i++)
            decode_3p_track(sig_pos[i], pulse_lo[i], 4, 1);
        for (i = 2; i < 4; i++)
            decode_2p_track(sig_pos[i], pulse_lo[i], 4, 1);
        break;
    case MODE_15k85:
        for (i = 0; i < 4; i++)
            decode_3p_track(sig_pos[i], pulse_lo[i], 4, 1);
        break;
    case MODE_18k25:
        for (i = 0; i < 4; i++)
            decode_4p_track(sig_pos[i], (int) pulse_lo[i] +
                           ((int) pulse_hi[i] << 14), 4, 1);
        break;
    case MODE_19k85:
        for (i = 0; i < 2; i++)
            decode_5p_track(sig_pos[i], (int) pulse_lo[i] +
                           ((int) pulse_hi[i] << 10), 4, 1);
        for (i = 2; i < 4; i++)
            decode_4p_track(sig_pos[i], (int) pulse_lo[i] +
                           ((int) pulse_hi[i] << 14), 4, 1);
        break;
    case MODE_23k05:
    case MODE_23k85:
        for (i = 0; i < 4; i++)
            decode_6p_track(sig_pos[i], (int) pulse_lo[i] +
                           ((int) pulse_hi[i] << 11), 4, 1);
        break;
    }

    memset(fixed_vector, 0, sizeof(float) * AMRWB_SFR_SIZE);

    for (i = 0; i < 4; i++)
        for (j = 0; j < pulses_nb_per_mode_tr[mode][i]; j++) {
            int pos = (FFABS(sig_pos[i][j]) - 1) * spacing + i;

            fixed_vector[pos] += sig_pos[i][j] < 0 ? -1.0 : 1.0;
        }
}