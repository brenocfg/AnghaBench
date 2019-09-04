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
struct TYPE_6__ {TYPE_1__* avframe; } ;
struct TYPE_5__ {int display_picture_number; } ;
typedef  TYPE_2__ DiracFrame ;

/* Variables and functions */

__attribute__((used)) static DiracFrame *remove_frame(DiracFrame *framelist[], int picnum)
{
    DiracFrame *remove_pic = NULL;
    int i, remove_idx = -1;

    for (i = 0; framelist[i]; i++)
        if (framelist[i]->avframe->display_picture_number == picnum) {
            remove_pic = framelist[i];
            remove_idx = i;
        }

    if (remove_pic)
        for (i = remove_idx; framelist[i]; i++)
            framelist[i] = framelist[i+1];

    return remove_pic;
}