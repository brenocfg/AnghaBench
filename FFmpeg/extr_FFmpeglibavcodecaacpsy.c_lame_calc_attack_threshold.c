#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int quality; float st_lrm; } ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 TYPE_1__* psy_abr_map ; 

__attribute__((used)) static float lame_calc_attack_threshold(int bitrate)
{
    /* Assume max bitrate to start with */
    int lower_range = 12, upper_range = 12;
    int lower_range_kbps = psy_abr_map[12].quality;
    int upper_range_kbps = psy_abr_map[12].quality;
    int i;

    /* Determine which bitrates the value specified falls between.
     * If the loop ends without breaking our above assumption of 320kbps was correct.
     */
    for (i = 1; i < 13; i++) {
        if (FFMAX(bitrate, psy_abr_map[i].quality) != bitrate) {
            upper_range = i;
            upper_range_kbps = psy_abr_map[i    ].quality;
            lower_range = i - 1;
            lower_range_kbps = psy_abr_map[i - 1].quality;
            break; /* Upper range found */
        }
    }

    /* Determine which range the value specified is closer to */
    if ((upper_range_kbps - bitrate) > (bitrate - lower_range_kbps))
        return psy_abr_map[lower_range].st_lrm;
    return psy_abr_map[upper_range].st_lrm;
}