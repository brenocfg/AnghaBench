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

/* Variables and functions */
 scalar_t__ AMRWB_P_DELAY_MAX ; 
 int /*<<< orphan*/  AMRWB_P_DELAY_MIN ; 
 scalar_t__ av_clip (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void decode_pitch_lag_high(int *lag_int, int *lag_frac, int pitch_index,
                                  uint8_t *base_lag_int, int subframe)
{
    if (subframe == 0 || subframe == 2) {
        if (pitch_index < 376) {
            *lag_int  = (pitch_index + 137) >> 2;
            *lag_frac = pitch_index - (*lag_int << 2) + 136;
        } else if (pitch_index < 440) {
            *lag_int  = (pitch_index + 257 - 376) >> 1;
            *lag_frac = (pitch_index - (*lag_int << 1) + 256 - 376) * 2;
            /* the actual resolution is 1/2 but expressed as 1/4 */
        } else {
            *lag_int  = pitch_index - 280;
            *lag_frac = 0;
        }
        /* minimum lag for next subframe */
        *base_lag_int = av_clip(*lag_int - 8 - (*lag_frac < 0),
                                AMRWB_P_DELAY_MIN, AMRWB_P_DELAY_MAX - 15);
        // XXX: the spec states clearly that *base_lag_int should be
        // the nearest integer to *lag_int (minus 8), but the ref code
        // actually always uses its floor, I'm following the latter
    } else {
        *lag_int  = (pitch_index + 1) >> 2;
        *lag_frac = pitch_index - (*lag_int << 2);
        *lag_int += *base_lag_int;
    }
}