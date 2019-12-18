#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* on_event ) (TYPE_1__*) ;scalar_t__ frame_ready; scalar_t__ eof; } ;
typedef  TYPE_1__ FFFrameSync ;

/* Variables and functions */
 int framesync_advance (TYPE_1__*) ; 
 int stub1 (TYPE_1__*) ; 

int ff_framesync_activate(FFFrameSync *fs)
{
    int ret;

    ret = framesync_advance(fs);
    if (ret < 0)
        return ret;
    if (fs->eof || !fs->frame_ready)
        return 0;
    ret = fs->on_event(fs);
    if (ret < 0)
        return ret;
    fs->frame_ready = 0;

    return 0;
}