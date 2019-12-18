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
typedef  enum AVFrameSideDataType { ____Placeholder_AVFrameSideDataType } AVFrameSideDataType ;
struct TYPE_6__ {int nb_side_data; TYPE_1__** side_data; } ;
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ AVFrameSideData ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  free_side_data (TYPE_1__**) ; 

void av_frame_remove_side_data(AVFrame *frame, enum AVFrameSideDataType type)
{
    int i;

    for (i = frame->nb_side_data - 1; i >= 0; i--) {
        AVFrameSideData *sd = frame->side_data[i];
        if (sd->type == type) {
            free_side_data(&frame->side_data[i]);
            frame->side_data[i] = frame->side_data[frame->nb_side_data - 1];
            frame->nb_side_data--;
        }
    }
}