#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/ * end; scalar_t__ nb_samples; scalar_t__ nb_frames; TYPE_2__* list; } ;
typedef  TYPE_1__ FrameList ;
typedef  TYPE_2__ FrameInfo ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_2__*) ; 

__attribute__((used)) static void frame_list_clear(FrameList *frame_list)
{
    if (frame_list) {
        while (frame_list->list) {
            FrameInfo *info = frame_list->list;
            frame_list->list = info->next;
            av_free(info);
        }
        frame_list->nb_frames  = 0;
        frame_list->nb_samples = 0;
        frame_list->end        = NULL;
    }
}