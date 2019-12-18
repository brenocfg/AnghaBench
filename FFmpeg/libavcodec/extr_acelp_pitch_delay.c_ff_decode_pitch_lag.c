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

/* Variables and functions */
 scalar_t__ PITCH_DELAY_MAX ; 
 int /*<<< orphan*/  PITCH_DELAY_MIN ; 
 int av_clip (int const,int /*<<< orphan*/ ,scalar_t__) ; 

void ff_decode_pitch_lag(int *lag_int, int *lag_frac, int pitch_index,
                         const int prev_lag_int, const int subframe,
                         int third_as_first, int resolution)
{
    /* Note n * 10923 >> 15 is floor(x/3) for 0 <= n <= 32767 */
    if (subframe == 0 || (subframe == 2 && third_as_first)) {

        if (pitch_index < 197)
            pitch_index += 59;
        else
            pitch_index = 3 * pitch_index - 335;

    } else {
        if (resolution == 4) {
            int search_range_min = av_clip(prev_lag_int - 5, PITCH_DELAY_MIN,
                                           PITCH_DELAY_MAX - 9);

            // decoding with 4-bit resolution
            if (pitch_index < 4) {
                // integer only precision for [search_range_min, search_range_min+3]
                pitch_index = 3 * (pitch_index + search_range_min) + 1;
            } else if (pitch_index < 12) {
                // 1/3 fractional precision for [search_range_min+3 1/3, search_range_min+5 2/3]
                pitch_index += 3 * search_range_min + 7;
            } else {
                // integer only precision for [search_range_min+6, search_range_min+9]
                pitch_index = 3 * (pitch_index + search_range_min - 6) + 1;
            }
        } else {
            // decoding with 5 or 6 bit resolution, 1/3 fractional precision
            pitch_index--;

            if (resolution == 5) {
                pitch_index += 3 * av_clip(prev_lag_int - 10, PITCH_DELAY_MIN,
                                           PITCH_DELAY_MAX - 19);
            } else
                pitch_index += 3 * av_clip(prev_lag_int - 5, PITCH_DELAY_MIN,
                                           PITCH_DELAY_MAX - 9);
        }
    }
    *lag_int  = pitch_index * 10923 >> 15;
    *lag_frac = pitch_index - 3 * *lag_int - 1;
}