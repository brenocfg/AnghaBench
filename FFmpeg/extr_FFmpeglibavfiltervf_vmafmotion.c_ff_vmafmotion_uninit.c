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
struct TYPE_3__ {double nb_frames; double motion_sum; int /*<<< orphan*/  temp_data; int /*<<< orphan*/ * blur_data; } ;
typedef  TYPE_1__ VMAFMotionData ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 

double ff_vmafmotion_uninit(VMAFMotionData *s)
{
    av_free(s->blur_data[0]);
    av_free(s->blur_data[1]);
    av_free(s->temp_data);

    return s->nb_frames > 0 ? s->motion_sum / s->nb_frames : 0.0;
}