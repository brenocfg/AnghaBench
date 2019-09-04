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
typedef  int uint64_t ;

/* Variables and functions */
 int AV_CH_BACK_LEFT ; 
 int AV_CH_BACK_RIGHT ; 
 int AV_CH_FRONT_LEFT ; 
 int AV_CH_FRONT_LEFT_OF_CENTER ; 
 int AV_CH_FRONT_RIGHT ; 
 int AV_CH_FRONT_RIGHT_OF_CENTER ; 
 int AV_CH_LAYOUT_SURROUND ; 
 int AV_CH_SIDE_LEFT ; 
 int AV_CH_SIDE_RIGHT ; 
 int AV_CH_STEREO_LEFT ; 
 int AV_CH_STEREO_RIGHT ; 
 int AV_CH_SURROUND_DIRECT_LEFT ; 
 int AV_CH_SURROUND_DIRECT_RIGHT ; 
 int AV_CH_TOP_BACK_LEFT ; 
 int AV_CH_TOP_BACK_RIGHT ; 
 int AV_CH_TOP_FRONT_LEFT ; 
 int AV_CH_TOP_FRONT_RIGHT ; 
 int AV_CH_WIDE_LEFT ; 
 int AV_CH_WIDE_RIGHT ; 
 int /*<<< orphan*/  even (int) ; 

__attribute__((used)) static int sane_layout(uint64_t layout)
{
    /* check that there is at least 1 front speaker */
    if (!(layout & AV_CH_LAYOUT_SURROUND))
        return 0;

    /* check for left/right symmetry */
    if (!even(layout & (AV_CH_FRONT_LEFT           | AV_CH_FRONT_RIGHT))           ||
        !even(layout & (AV_CH_SIDE_LEFT            | AV_CH_SIDE_RIGHT))            ||
        !even(layout & (AV_CH_BACK_LEFT            | AV_CH_BACK_RIGHT))            ||
        !even(layout & (AV_CH_FRONT_LEFT_OF_CENTER | AV_CH_FRONT_RIGHT_OF_CENTER)) ||
        !even(layout & (AV_CH_TOP_FRONT_LEFT       | AV_CH_TOP_FRONT_RIGHT))       ||
        !even(layout & (AV_CH_TOP_BACK_LEFT        | AV_CH_TOP_BACK_RIGHT))        ||
        !even(layout & (AV_CH_STEREO_LEFT          | AV_CH_STEREO_RIGHT))          ||
        !even(layout & (AV_CH_WIDE_LEFT            | AV_CH_WIDE_RIGHT))            ||
        !even(layout & (AV_CH_SURROUND_DIRECT_LEFT | AV_CH_SURROUND_DIRECT_RIGHT)))
        return 0;

    return 1;
}