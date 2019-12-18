#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  frame; TYPE_2__* surface; } ;
struct TYPE_5__ {int /*<<< orphan*/  Locked; } ;
struct TYPE_6__ {TYPE_1__ Data; } ;
typedef  TYPE_3__ QSVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_unused_frames(QSVFrame *list)
{
    while (list) {
        if (list->surface && !list->surface->Data.Locked) {
            list->surface = NULL;
            av_frame_free(&list->frame);
        }
        list = list->next;
    }
}