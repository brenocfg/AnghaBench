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
struct TYPE_5__ {scalar_t__ streaming; int /*<<< orphan*/  video; } ;
typedef  TYPE_1__ zbar_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_poll (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_video_handler ; 
 int /*<<< orphan*/  remove_poll (TYPE_1__*,int) ; 
 int zbar_video_get_fd (int /*<<< orphan*/ ) ; 

int _zbar_processor_enable (zbar_processor_t *proc)
{
    int vid_fd = zbar_video_get_fd(proc->video);
    if(vid_fd < 0)
        return(0);

    if(proc->streaming)
        add_poll(proc, vid_fd, proc_video_handler);
    else
        remove_poll(proc, vid_fd);
    /* FIXME failure recovery? */
    return(0);
}