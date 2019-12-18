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
struct TYPE_5__ {TYPE_1__* list; } ;
struct TYPE_4__ {int nb_samples; } ;
typedef  TYPE_2__ FrameList ;

/* Variables and functions */

__attribute__((used)) static int frame_list_next_frame_size(FrameList *frame_list)
{
    if (!frame_list->list)
        return 0;
    return frame_list->list->nb_samples;
}