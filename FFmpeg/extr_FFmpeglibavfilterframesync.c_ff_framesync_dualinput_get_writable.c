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
struct TYPE_6__ {TYPE_1__* parent; } ;
struct TYPE_5__ {int /*<<< orphan*/ * inputs; } ;
typedef  TYPE_2__ FFFrameSync ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int ff_framesync_dualinput_get (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int ff_inlink_make_frame_writable (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int ff_framesync_dualinput_get_writable(FFFrameSync *fs, AVFrame **f0, AVFrame **f1)
{
    int ret;

    ret = ff_framesync_dualinput_get(fs, f0, f1);
    if (ret < 0)
        return ret;
    ret = ff_inlink_make_frame_writable(fs->parent->inputs[0], f0);
    if (ret < 0) {
        av_frame_free(f0);
        *f1 = NULL;
        return ret;
    }
    return 0;
}