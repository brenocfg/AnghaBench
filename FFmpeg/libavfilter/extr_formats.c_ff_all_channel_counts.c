#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int all_layouts; int all_counts; } ;
typedef  TYPE_1__ AVFilterChannelLayouts ;

/* Variables and functions */
 TYPE_1__* av_mallocz (int) ; 

AVFilterChannelLayouts *ff_all_channel_counts(void)
{
    AVFilterChannelLayouts *ret = av_mallocz(sizeof(*ret));
    if (!ret)
        return NULL;
    ret->all_layouts = ret->all_counts = 1;
    return ret;
}