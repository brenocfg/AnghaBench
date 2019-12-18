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
typedef  int int64_t ;

/* Variables and functions */
 int AV_CH_LOW_FREQUENCY ; 
 int AV_CH_LOW_FREQUENCY_2 ; 

int hb_layout_get_low_freq_channel_count(int64_t layout)
{
    return !!(layout & AV_CH_LOW_FREQUENCY) +
           !!(layout & AV_CH_LOW_FREQUENCY_2);
}