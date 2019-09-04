#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int all_layouts; int all_counts; scalar_t__ nb_channel_layouts; } ;
typedef  TYPE_1__ AVFilterChannelLayouts ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void sanitize_channel_layouts(void *log, AVFilterChannelLayouts *l)
{
    if (!l)
        return;
    if (l->nb_channel_layouts) {
        if (l->all_layouts || l->all_counts)
            av_log(log, AV_LOG_WARNING, "All layouts set on non-empty list\n");
        l->all_layouts = l->all_counts = 0;
    } else {
        if (l->all_counts && !l->all_layouts)
            av_log(log, AV_LOG_WARNING, "All counts without all layouts\n");
        l->all_layouts = 1;
    }
}