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
typedef  scalar_t__ uint8_t ;
typedef  enum Mode { ____Placeholder_Mode } Mode ;

/* Variables and functions */
 scalar_t__ AMRWB_P_DELAY_MAX ; 
 int /*<<< orphan*/  AMRWB_P_DELAY_MIN ; 
 int MODE_6k60 ; 
 scalar_t__ av_clip (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void decode_pitch_lag_low(int *lag_int, int *lag_frac, int pitch_index,
                                 uint8_t *base_lag_int, int subframe, enum Mode mode)
{
    if (subframe == 0 || (subframe == 2 && mode != MODE_6k60)) {
        if (pitch_index < 116) {
            *lag_int  = (pitch_index + 69) >> 1;
            *lag_frac = (pitch_index - (*lag_int << 1) + 68) * 2;
        } else {
            *lag_int  = pitch_index - 24;
            *lag_frac = 0;
        }
        // XXX: same problem as before
        *base_lag_int = av_clip(*lag_int - 8 - (*lag_frac < 0),
                                AMRWB_P_DELAY_MIN, AMRWB_P_DELAY_MAX - 15);
    } else {
        *lag_int  = (pitch_index + 1) >> 1;
        *lag_frac = (pitch_index - (*lag_int << 1)) * 2;
        *lag_int += *base_lag_int;
    }
}