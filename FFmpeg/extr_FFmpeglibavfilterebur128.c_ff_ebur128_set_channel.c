#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int channels; TYPE_1__* d; } ;
struct TYPE_4__ {int* channel_map; } ;
typedef  TYPE_2__ FFEBUR128State ;

/* Variables and functions */
 int FF_EBUR128_DUAL_MONO ; 

int ff_ebur128_set_channel(FFEBUR128State * st,
                           unsigned int channel_number, int value)
{
    if (channel_number >= st->channels) {
        return 1;
    }
    if (value == FF_EBUR128_DUAL_MONO &&
        (st->channels != 1 || channel_number != 0)) {
        return 1;
    }
    st->d->channel_map[channel_number] = value;
    return 0;
}